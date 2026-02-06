
#include "GameSettingsMenu.h"
#include "AimTrainer/Gameplay/AimTrainerPlayerController.h"

void UGameSettingsMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GameInstance = World->GetGameInstance())
		{
			ProfileManager = GameInstance->GetSubsystem<UGameProfileManager>();
		}
	}

	UserSettings = UAimTrainerUserSettings::GetAimTrainerUserSettings();

	ProfileComboBox->ClearOptions();
	const TArray<FGameProfile> Profiles = ProfileManager->GetProfiles();
	for (const FGameProfile& Profile : Profiles)
	{
		ProfileComboBox->AddOption(Profile.ProfileName);
	}
	
	if (UserSettings)
	{
		ProfileComboBox->SetSelectedOption(UserSettings->CurrentGameProfile);

		if (SensitivitySliderTextBox)
		{
			SensitivitySliderTextBox->SetValue(UserSettings->MouseSensitivity);
		}
		if (FOVSliderTextBox)
		{
			FOVSliderTextBox->SetValue(UserSettings->FieldOfView);
		}
	}

}

void UGameSettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &UGameSettingsMenu::ApplyOnClicked);
	}

	if (SensitivitySliderTextBox)
	{
		SensitivitySliderTextBox->OnValueChanged.AddDynamic(this, &UGameSettingsMenu::OnSensitivitySliderChanged);
	}
	
	if (FOVSliderTextBox)
	{
		FOVSliderTextBox->OnValueChanged.AddDynamic(this, &UGameSettingsMenu::OnFOVSliderChanged);
	}
}

void UGameSettingsMenu::OnSensitivitySliderChanged(float NewValue)
{
}

void UGameSettingsMenu::OnFOVSliderChanged(float NewValue)
{
}

void UGameSettingsMenu::ApplyOnClicked()
{
	if (UserSettings)
	{
		UserSettings->CurrentGameProfile = ProfileComboBox->GetSelectedOption();
		UserSettings->MouseSensitivity = SensitivitySliderTextBox->GetValue();
		UserSettings->FieldOfView = FOVSliderTextBox->GetValue();

		UserSettings->SaveSettings();
		
		AAimTrainerPlayerController* PC = Cast<AAimTrainerPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC)
		{
			PC->ApplyFOV();
		}

		UE_LOG(LogTemp, Log, TEXT("Settings applied: Profile=%s, Sensitivity=%f, FOV=%f"),
			*UserSettings->CurrentGameProfile,
			UserSettings->MouseSensitivity,
			UserSettings->FieldOfView);
	}
}