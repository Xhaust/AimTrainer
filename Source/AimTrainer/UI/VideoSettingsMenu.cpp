#include "VideoSettingsMenu.h"

#include "AimTrainer/Settings/AimTrainerUserSettings.h"

void UVideoSettingsMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ResolutionCombo->AddOption("1280x720");
	ResolutionCombo->AddOption("1920x1080");
	ResolutionCombo->AddOption("2560x1440");

	WindowModeCombo->AddOption("Fullscreen");
	WindowModeCombo->AddOption("Windowed");
	WindowModeCombo->AddOption("Borderless");

	QualityCombo->AddOption("Low");
	QualityCombo->AddOption("Medium");
	QualityCombo->AddOption("High");
	QualityCombo->AddOption("Epic");

	ApplyButton->OnClicked.AddDynamic(this, &ThisClass::OnApplyClicked);
}

void UVideoSettingsMenu::OnApplyClicked()
{
	UAimTrainerUserSettings* Save = UAimTrainerUserSettings::GetAimTrainerUserSettings();
	UGameUserSettings* GS = GEngine->GetGameUserSettings();
	if (!Save || !GS) return;

	FString Res = ResolutionCombo->GetSelectedOption();
	FString XStr, YStr;
	if (Res.Split("x", &XStr, &YStr))
	{
		int32 X = FCString::Atoi(*XStr);
		int32 Y = FCString::Atoi(*YStr);
		GS->SetScreenResolution(FIntPoint(X, Y));
		Save->Resolution = FIntPoint(X, Y);
	}

	const FString Mode = WindowModeCombo->GetSelectedOption();
	EWindowMode::Type WindowMode =
		Mode == "Windowed" ? EWindowMode::Windowed :
		Mode == "Borderless" ? EWindowMode::WindowedFullscreen :
		EWindowMode::Fullscreen;

	GS->SetFullscreenMode(WindowMode);
	Save->WindowMode = WindowMode;

	const int32 Quality = QualityCombo->GetSelectedIndex();
	GS->SetOverallScalabilityLevel(Quality);
	Save->OverallQuality = Quality;

	GS->SetVSyncEnabled(VSyncCheckBox->IsChecked());
	Save->bVSync = VSyncCheckBox->IsChecked();

	GS->ApplySettings(false);
	Save->SaveSettings();
}