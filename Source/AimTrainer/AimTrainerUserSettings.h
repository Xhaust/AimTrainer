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

	UAimTrainerUserSettings();
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Controls")
	FString CurrentGameProfile;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float MouseSensitivity;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float FieldOfView;

	UFUNCTION(BlueprintCallable, BlueprintCallable, Category = "Settings")
	void ApplyAimTrainerSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	static UAimTrainerUserSettings* GetAimTrainerUserSettings();
};

