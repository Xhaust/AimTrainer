#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameProfileManager.generated.h"

USTRUCT(BlueprintType)
struct FGameProfile
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Profile")
	FString ProfileName = "CS2";

	UPROPERTY(EditDefaultsOnly, Category = "Profile")
	float ConversionScale = 1.0f;
};

UCLASS()
class AIMTRAINER_API UGameProfileManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY(EditAnywhere, Category="Profiles")
	TArray<FGameProfile> Profiles;
	
	UFUNCTION()
	TArray<FGameProfile> GetProfiles();

	float GetConversionScaleForProfile(const FString& ProfileName) const;
};
