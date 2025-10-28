// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "AimTrainerUserSettings.generated.h"

/**
 * 
 */
UCLASS(Config=GameUserSettings)
class AIMTRAINER_API UAimTrainerUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

	UPROPERTY(Config, EditAnywhere, Category="Controls")
	FString CurrentGameProfile;
	
	UPROPERTY(Config, EditAnywhere, Category = "Controls")
	float MouseSensitivity;

	UPROPERTY(Config, EditAnywhere, Category = "Controls")
	float FieldOfView;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ApplyAimTrainerSettings();

	static UAimTrainerUserSettings* GetAimTrainerUserSettings();
};

