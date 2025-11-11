// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettingsMenu.h"


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
		SensitivitySlider->SetValue(UserSettings->MouseSensitivity);
		FOVSlider->SetValue(UserSettings->FieldOfView);
	}

}

void UGameSettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ApplyButton)
	{
		ApplyButton->OnClicked.AddDynamic(this, &UGameSettingsMenu::ApplyOnClicked);
	}
}

void UGameSettingsMenu::ApplyOnClicked()
{
	if (UserSettings)
	{
		UserSettings->CurrentGameProfile = ProfileComboBox->GetSelectedOption();
		UserSettings->MouseSensitivity = SensitivitySlider->GetValue();
		UserSettings->FieldOfView = FOVSlider->GetValue();

		UserSettings->SaveSettings();

		UE_LOG(LogTemp, Log, TEXT("Settings applied: Profile=%s, Sensitivity=%f, FOV=%f"),
			*UserSettings->CurrentGameProfile,
			UserSettings->MouseSensitivity,
			UserSettings->FieldOfView);
	}
}
