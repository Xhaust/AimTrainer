// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Settings = UAimTrainerUserSettings::GetAimTrainerUserSettings();

	if (DefaultWeaponClass)
	{
		// Spawn the weapon
		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
		if (CurrentWeapon)
		{
			// Set the owner (important for line trace and ApplyDamage)
			CurrentWeapon->SetOwner(this);
		}
	}

	if (CrosshairClass)
	{
		Crosshair = CreateWidget<UCrosshair>(GetWorld(), CrosshairClass);
		if (Crosshair)
		{
			Crosshair->AddToViewport();
		}
	}
		ApplyFOV();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = GetController<APlayerController>();
	check(PlayerController);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(BaseMappingContext, 0);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayerCharacter::StartFire);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopFire);
		EnhancedInputComponent->BindAction(ToggleSettingsAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleSettingsMenu);
	}

}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	UGameProfileManager* ProfileManager = GetGameInstance()->GetSubsystem<UGameProfileManager>();
	float MouseSensitivity = Settings->MouseSensitivity;
	float ConversionScaler = ProfileManager->GetConversionScaleForProfile(Settings->CurrentGameProfile);
	MouseSensitivity *= ConversionScaler;
	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X * MouseSensitivity);
		AddControllerPitchInput(LookAxisVector.Y * MouseSensitivity);
	}
}

void APlayerCharacter::StartFire()
{
	if (bIsSettingsOpen)
	{
		return;
	}
	
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void APlayerCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void APlayerCharacter::ToggleSettingsMenu()
{
	if (SettingsMenuClass)
	{
		APlayerController* PlayerController = GetController<APlayerController>();
		if (PlayerController)
		{
			if (SettingsMenu && SettingsMenu->IsInViewport())
			{
				bIsSettingsOpen = false;
				
				SettingsMenu->RemoveFromParent();
				SettingsMenu = nullptr;
				FInputModeGameOnly GameInputMode;
				PlayerController->SetInputMode(GameInputMode);
				PlayerController->bShowMouseCursor = false;
				PlayerController->SetIgnoreLookInput(false);
				return;
			}
			if (!SettingsMenu)
			{
			SettingsMenu = CreateWidget<UGameSettingsMenu>(PlayerController, SettingsMenuClass);
			}
			if (SettingsMenu)
			{
				bIsSettingsOpen = true;	
				
				SettingsMenu->AddToViewport();
				FInputModeGameAndUI GameAndUIInputMode;
				GameAndUIInputMode.SetWidgetToFocus(SettingsMenu->TakeWidget());
				GameAndUIInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PlayerController->SetInputMode(GameAndUIInputMode);
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetIgnoreLookInput(true);
			}
		}
	}
}

void APlayerCharacter::ApplyFOV()
{
	if (Settings)
	{
		APlayerController* PlayerController = GetController<APlayerController>();
		if (PlayerController)
		{
			PlayerController->PlayerCameraManager->SetFOV(Settings->FieldOfView);
		}
	}
}