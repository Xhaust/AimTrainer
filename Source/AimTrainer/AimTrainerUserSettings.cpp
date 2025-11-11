// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrainerUserSettings.h"

UAimTrainerUserSettings* UAimTrainerUserSettings::GetAimTrainerUserSettings()
{
	return Cast<UAimTrainerUserSettings>(GetGameUserSettings());
}
