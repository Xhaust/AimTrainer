
#include "AimTrainerPlayerController.h"
#include "AimTrainerGameInstance.h"
#include "AimTrainerGameMode.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "Target.h"
#include "AimTrainer/Utils/RuntimeAssetLoader.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"

template <typename TWidget>
void OpenMenuWidget(
	AAimTrainerPlayerController* Controller,
	TWidget*& WidgetInstance,
	TSubclassOf<TWidget> WidgetClass,
	bool bCloseExistingMenus)
{
	if (!Controller)
	{
		return;
	}

	if (bCloseExistingMenus)
	{
		Controller->CloseAllMenus();
	}

	if (!WidgetInstance && WidgetClass)
	{
		WidgetInstance = CreateWidget<TWidget>(Controller, WidgetClass);
	}

	if (WidgetInstance)
	{
		WidgetInstance->AddToViewport();

		FInputModeGameAndUI Mode;
		Mode.SetHideCursorDuringCapture(false);
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		Controller->SetInputMode(Mode);
		Controller->SetShowMouseCursor(true);
	}
}

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
	OpenMenuWidget(this, MainMenu, MainMenuClass, false);
}

void AAimTrainerPlayerController::OpenSettingsMenu()
{
	OpenMenuWidget(this, SettingsMenu, SettingsMenuClass, true);
}

void AAimTrainerPlayerController::OpenVideoSettingsMenu()
{
	OpenMenuWidget(this, VideoSettingsMenu, VideoSettingsMenuClass, true);
}

void AAimTrainerPlayerController::OpenMapSelector()
{
	OpenMenuWidget(this, MapSelector, MapSelectorClass, true);
}

void AAimTrainerPlayerController::OpenCrosshairSelector()
{
	OpenMenuWidget(this, CrosshairSelector, CrosshairSelectorClass, true);
}

void AAimTrainerPlayerController::OpenScoreboard()
{
	OpenMenuWidget(this, Scoreboard, ScoreboardClass, true);
}

void AAimTrainerPlayerController::OpenColorPicker()
{
	CloseAllMenus();

	if (!ColorPicker && ColorPickerClass)
	{
		ColorPicker = CreateWidget<UColorPicker>(this, ColorPickerClass);
	}

	if (ColorPicker)
	{
		ColorPicker->OnColorSelected.RemoveDynamic(this, &ThisClass::HandleColorSelected);
		ColorPicker->OnColorSelected.AddDynamic(this, &ThisClass::HandleColorSelected);

		if (UserSettings)
		{
			ColorPicker->OnColorButtonClicked(UserSettings->TargetColor);
		}

		ColorPicker->AddToViewport();
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
	if (VideoSettingsMenu) { VideoSettingsMenu->RemoveFromParent(); VideoSettingsMenu = nullptr; }
	if (MainMenu) { MainMenu->RemoveFromParent(); MainMenu = nullptr; }
	if (CrosshairSelector) { CrosshairSelector->RemoveFromParent(); CrosshairSelector = nullptr; }
	if (ColorPicker) { ColorPicker->RemoveFromParent(); ColorPicker = nullptr; }

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AAimTrainerPlayerController::HandleColorSelected(FLinearColor SelectedColor)
{
	if (UserSettings)
	{
		UserSettings->TargetColor = SelectedColor;
		UserSettings->SaveSettings();
	}

	ApplyTargetColorToLiveTargets(SelectedColor);
}

void AAimTrainerPlayerController::ApplyTargetColorToLiveTargets(const FLinearColor& SelectedColor) const
{
	if (!GetWorld())
	{
		return;
	}

	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget::StaticClass(), TargetActors);

	for (AActor* TargetActor : TargetActors)
	{
		ATarget* Target = Cast<ATarget>(TargetActor);
		if (!Target)
		{
			continue;
		}

		TInlineComponentArray<UMeshComponent*> MeshComponents(Target);
		Target->GetComponents(MeshComponents);

		for (UMeshComponent* Mesh : MeshComponents)
		{
			if (!Mesh)
			{
				continue;
			}

			const int32 MaterialCount = Mesh->GetNumMaterials();
			for (int32 Index = 0; Index < MaterialCount; ++Index)
			{
				if (UMaterialInstanceDynamic* DynamicMat = Mesh->CreateAndSetMaterialInstanceDynamic(Index))
				{
					DynamicMat->SetVectorParameterValue(TEXT("TargetColor"), SelectedColor);
					DynamicMat->SetVectorParameterValue(TEXT("Color"), SelectedColor);
				}
			}
		}
	}
}

bool AAimTrainerPlayerController::AnyMenuOpen() const
{
	return (Scoreboard || MapSelector || SettingsMenu || VideoSettingsMenu || MainMenu || CrosshairSelector || ColorPicker);
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
	if (FullPath.IsEmpty() || !Crosshair) return;

	URuntimeAssetLoader* Loader = NewObject<URuntimeAssetLoader>(this);
	UTexture2D* Texture = Loader ? Loader->LoadTextureFromFile(FullPath) : nullptr;

	if (!Texture) return;

	Crosshair->SetCrosshairTexture(Texture);
}