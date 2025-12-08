// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrainerGameInstance.h"

void UAimTrainerGameInstance::Init()
{
	Super::Init();

	AimTrainerUserSettings = UAimTrainerUserSettings::GetAimTrainerUserSettings();
	if (AimTrainerUserSettings)
	{
		AimTrainerUserSettings->LoadSettings();
	}
}