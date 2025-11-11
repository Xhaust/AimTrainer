// Fill out your copyright notice in the Description page of Project Settings.


#include "GameProfileManager.h"

void UGameProfileManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Profiles = {
		FGameProfile{TEXT("CS2"), 1.0f},
		FGameProfile{TEXT("Valorant"), 0.314f},
		FGameProfile{TEXT("Overwatch"), 4.44f},
	};
}

TArray<FGameProfile> UGameProfileManager::GetProfiles()
{
	return Profiles;
}
