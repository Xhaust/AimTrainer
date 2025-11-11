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
	
public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Controls")
	FString CurrentGameProfile = "CS2";
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float MouseSensitivity = 1.0f;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float FieldOfView = 90.0f;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	static UAimTrainerUserSettings* GetAimTrainerUserSettings();
};

