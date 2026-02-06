
#include "GameProfileManager.h"

void UGameProfileManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Profiles = {
		FGameProfile{TEXT("CS2"), 1.0f},
		FGameProfile{TEXT("Valorant"), 3.18f},
		FGameProfile{TEXT("Overwatch"), 0.3f},
	};
}

TArray<FGameProfile> UGameProfileManager::GetProfiles()
{
	return Profiles;
}

float UGameProfileManager::GetConversionScaleForProfile(const FString& ProfileName) const
{
	for (const FGameProfile& Profile : Profiles)
	{
		if (Profile.ProfileName == ProfileName)
		{
			return Profile.ConversionScale;
		}
	}
	return 1.0f;
}
