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

	UAimTrainerUserSettings* UserSettings = UAimTrainerUserSettings::GetAimTrainerUserSettings();

	if (UserSettings)
	{
		ResolutionCombo->SetSelectedOption(
			UserSettings->Resolution == FIntPoint(1280, 720) ? "1280x720" :
			UserSettings->Resolution == FIntPoint(1920, 1080) ? "1920x1080" : "2560x1440");

		WindowModeCombo->SetSelectedOption(
			UserSettings->WindowMode == EWindowMode::Fullscreen ? "Fullscreen" :
			UserSettings->WindowMode == EWindowMode::Windowed ? "Windowed" : "Borderless"
		);

		QualityCombo->SetSelectedOption(
			UserSettings->OverallQuality == 0 ? "Low" :
			UserSettings->OverallQuality == 1 ? "Medium" :
			UserSettings->OverallQuality == 2 ? "High" : "Epic"
		);

		VSyncCheckBox->SetIsChecked(UserSettings->bVSync);
	}
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