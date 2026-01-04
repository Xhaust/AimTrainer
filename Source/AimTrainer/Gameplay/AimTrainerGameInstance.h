// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Settings/AimTrainerUserSettings.h"
#include "AimTrainerGameInstance.generated.h"

UCLASS()
class AIMTRAINER_API UAimTrainerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init()override;

	UFUNCTION()
	UAimTrainerUserSettings* GetAimTrainerUserSettings() const { return AimTrainerUserSettings; }

	UFUNCTION(BlueprintCallable)
	FString GetCurrentMapName() const;	

private:
	UPROPERTY()
	UAimTrainerUserSettings* AimTrainerUserSettings;
};
