// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrainerPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"

void AAimTrainerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UserSettings = UAimTrainerUserSettings::GetAimTrainerUserSettings();

	// Enhanced Input mapping
	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(BaseMappingContext, 0);
		}
	}

	// Crosshair
	if (CrosshairClass)
	{
		Crosshair = CreateWidget<UCrosshair>(this, CrosshairClass);
		if (Crosshair)
		{
			Crosshair->AddToViewport();
		}
	}

	ApplyFOV();
}

void AAimTrainerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this,
			&AAimTrainerPlayerController::HandleLook);

		EIC->BindAction(ShootAction, ETriggerEvent::Started, this,
			&AAimTrainerPlayerController::HandleStartFire);

		EIC->BindAction(ShootAction, ETriggerEvent::Completed, this,
			&AAimTrainerPlayerController::HandleStopFire);

		EIC->BindAction(ToggleSettingsAction, ETriggerEvent::Started, this,
			&AAimTrainerPlayerController::HandleEscape);
	}
}

// ===== Input Handlers =====

void AAimTrainerPlayerController::HandleLook(const FInputActionValue& Value)
{
	if (bSettingsOpen) return;

	// get raw axis
	const FVector2D RawLook = Value.Get<FVector2D>();

	// get user settings sensitivity
	UAimTrainerUserSettings* Settings = UAimTrainerUserSettings::GetAimTrainerUserSettings();
	const float UserSensitivity = (Settings ? Settings->MouseSensitivity : 1.0f);

	//  apply profile conversion scale
	float ConversionScale = 1.0f;
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UGameProfileManager* PM = GI->GetSubsystem<UGameProfileManager>())
		{
			ConversionScale = PM->GetConversionScaleForProfile(Settings->CurrentGameProfile);
		}
	}

	const FVector2D ScaledLook = RawLook * UserSensitivity * ConversionScale;

	if (APlayerCharacter* PC = GetPawn<APlayerCharacter>())
	{
		PC->Look(FInputActionValue(ScaledLook));
	}
}

void AAimTrainerPlayerController::HandleStartFire()
{
	if (bSettingsOpen) return;

	if (APlayerCharacter* PC = GetPawn<APlayerCharacter>())
	{
		PC->StartFire();
	}
}

void AAimTrainerPlayerController::HandleStopFire()
{
	if (APlayerCharacter* PC = GetPawn<APlayerCharacter>())
	{
		PC->StopFire();
	}
}

void AAimTrainerPlayerController::HandleEscape()
{
	if (bSettingsOpen)
	{
		CloseSettingsMenu();
	}
	else
	{
		OpenSettingsMenu();
	}
}

// ===== UI =====

void AAimTrainerPlayerController::OpenSettingsMenu()
{
	if (!SettingsMenu && SettingsMenuClass)
	{
		SettingsMenu = CreateWidget<UGameSettingsMenu>(this, SettingsMenuClass);
	}

	if (SettingsMenu)
	{
		SettingsMenu->AddToViewport();
		bSettingsOpen = true;

		FInputModeGameAndUI Mode;
		Mode.SetWidgetToFocus(SettingsMenu->TakeWidget());
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);

		bShowMouseCursor = true;
	}
}

void AAimTrainerPlayerController::CloseSettingsMenu()
{
	if (SettingsMenu)
	{
		SettingsMenu->RemoveFromParent();
		SettingsMenu = nullptr;
	}

	bSettingsOpen = false;

	FInputModeGameOnly Mode;
	SetInputMode(Mode);

	bShowMouseCursor = false;
}

// ===== Camera =====

void AAimTrainerPlayerController::ApplyFOV()
{
	UAimTrainerUserSettings* Settings =
			UAimTrainerUserSettings::GetAimTrainerUserSettings();

	if (Settings && PlayerCameraManager)
	{
		PlayerCameraManager->SetFOV(Settings->FieldOfView);
	}
}