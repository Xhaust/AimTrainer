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

FString UAimTrainerGameInstance::GetCurrentMapName() const
{
	if (!GetWorld()) return TEXT("Unknown");

	FString MapName = GetWorld()->GetMapName();

	// Remove PIE prefix (UEDPIE_0_)
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	return MapName;
}