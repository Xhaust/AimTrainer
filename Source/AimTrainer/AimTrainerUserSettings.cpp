// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrainerUserSettings.h"

UAimTrainerUserSettings::UAimTrainerUserSettings()
{
	MouseSensitivity = 1.0f;
	FieldOfView = 103.0f;
}

void UAimTrainerUserSettings::ApplyAimTrainerSettings()
{
	SaveConfig();
}

UAimTrainerUserSettings* UAimTrainerUserSettings::GetAimTrainerUserSettings()
{
	return Cast<UAimTrainerUserSettings>(UGameUserSettings::GetGameUserSettings());
}
