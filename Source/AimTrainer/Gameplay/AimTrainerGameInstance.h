// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Settings/AimTrainerUserSettings.h"
#include "AimTrainerGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FMapInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString LabelName;

	UPROPERTY(EditAnywhere)
	FName LevelName;
};

UCLASS()
class AIMTRAINER_API UAimTrainerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init()override;

	UFUNCTION()
	UAimTrainerUserSettings* GetAimTrainerUserSettings() const { return AimTrainerUserSettings; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Maps")
	TArray<FMapInfo> AvailableMaps;

	UPROPERTY(BlueprintReadWrite)
	FString CurrentScenarioName = TEXT("Tile Frenzy");

private:
	UPROPERTY()
	UAimTrainerUserSettings* AimTrainerUserSettings;
};
