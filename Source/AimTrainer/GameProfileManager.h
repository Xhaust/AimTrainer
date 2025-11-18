// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameProfileManager.generated.h"

USTRUCT(BlueprintType)
struct FGameProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Profile")
	FString ProfileName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Profile")
	float ConversionScale;
};

UCLASS()
class AIMTRAINER_API UGameProfileManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY(EditAnywhere, Category="Profiles")
	TArray<FGameProfile> Profiles;
	
	UFUNCTION(BlueprintCallable, Category = "Profiles")
	TArray<FGameProfile> GetProfiles();
	
};
