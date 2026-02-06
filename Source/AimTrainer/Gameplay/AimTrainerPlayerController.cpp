
#include "AimTrainerPlayerController.h"
#include "AimTrainerGameInstance.h"
#include "AimTrainerGameMode.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "AimTrainer/Utils/RuntimeAssetLoader.h"
#include "Kismet/GameplayStatics.h"

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

	if (AAimTrainerGameMode* GM = Cast<AAimTrainerGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnSessionEnded.AddDynamic(this, &ThisClass::OpenScoreboard);
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

		EIC->BindAction(ToggleMenuAction, ETriggerEvent::Started, this,
			&AAimTrainerPlayerController::HandleEscape);
	}
}

// ===== Input Handlers =====

void AAimTrainerPlayerController::HandleLook(const FInputActionValue& Value)
{
	if (AnyMenuOpen()) return;

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
	if (AnyMenuOpen()) return;

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
	if (AnyMenuOpen())
	{
		CloseAllMenus();
	}
	else
	{
		OpenMainMenu();
	}
}

// ===== UI =====

void AAimTrainerPlayerController::OpenMainMenu()
{
	if (!MainMenu && MainMenuClass)
	{
		MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	}

	if (MainMenu)
	{
		MainMenu->AddToViewport();
		FInputModeGameAndUI Mode;
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
}

void AAimTrainerPlayerController::OpenSettingsMenu()
{
	CloseAllMenus();

	if (!SettingsMenu && SettingsMenuClass)
	{
		SettingsMenu = CreateWidget<UGameSettingsMenu>(this, SettingsMenuClass);
	}

	if (SettingsMenu)
	{
		SettingsMenu->AddToViewport();
		FInputModeGameAndUI Mode;
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
}

void AAimTrainerPlayerController::OpenMapSelector()
{
	CloseAllMenus();

	if (!MapSelector && MapSelectorClass)
	{
		MapSelector = CreateWidget<UMapSelectorWidget>(this, MapSelectorClass);
	}

	if (MapSelector)
	{
		MapSelector->AddToViewport();
		FInputModeGameAndUI Mode;
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
}

void AAimTrainerPlayerController::OpenCrosshairSelector()
{
	CloseAllMenus();

	if (!CrosshairSelector && CrosshairSelectorClass)
	{
		CrosshairSelector = CreateWidget<UCrosshairSelectorWidget>(this, CrosshairSelectorClass);
	}

	if (CrosshairSelector)
	{
		CrosshairSelector->AddToViewport();
		FInputModeGameAndUI Mode;
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
}

void AAimTrainerPlayerController::OpenScoreboard()
{
	CloseAllMenus();
	
	if (!Scoreboard && ScoreboardClass)
	{
		Scoreboard = CreateWidget<UScoreboard>(this, ScoreboardClass);
	}

	if (Scoreboard)
	{
		Scoreboard->AddToViewport();
		FInputModeGameAndUI Mode;
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
}

void AAimTrainerPlayerController::CloseAllMenus()
{
	if (Scoreboard) { Scoreboard->RemoveFromParent(); Scoreboard = nullptr; }
	if (MapSelector) { MapSelector->RemoveFromParent(); MapSelector = nullptr; }
	if (SettingsMenu) { SettingsMenu->RemoveFromParent(); SettingsMenu = nullptr; }
	if (MainMenu) { MainMenu->RemoveFromParent(); MainMenu = nullptr; }
	if (CrosshairSelector) { CrosshairSelector->RemoveFromParent(); CrosshairSelector = nullptr; }

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

bool AAimTrainerPlayerController::AnyMenuOpen() const
{
	return (Scoreboard || MapSelector || SettingsMenu || MainMenu);
}

void AAimTrainerPlayerController::LoadMap(FName MapName)
{
	if (MapName.IsNone()) return;

	UGameplayStatics::OpenLevel(this, MapName);
	CloseAllMenus();

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


void AAimTrainerPlayerController::ApplyCrosshairFromFile(const FString& FullPath)
{
	UTexture2D* Texture =
		URuntimeAssetLoader::LoadTextureFromFile(FullPath);

	if (!Texture || !Crosshair) return;

	Crosshair->SetCrosshairTexture(Texture);

	Crosshair->AddToViewport();
}