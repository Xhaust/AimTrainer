// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "AimTrainerUserSettings.generated.h"

UCLASS(Config=GameUserSettings)
class AIMTRAINER_API UAimTrainerUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditDefaultsOnly, Category="Controls")
	FString CurrentGameProfile = "CS2";
	
	UPROPERTY(Config, EditDefaultsOnly, Category = "Controls")
	float MouseSensitivity = 1.0f;

	UPROPERTY(Config, EditDefaultsOnly, Category = "Controls")
	float FieldOfView = 90.0f;

	UPROPERTY(Config, EditAnywhere, Category = "Crosshair")
	TSoftObjectPtr<UTexture2D> CrosshairTexture = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Game/Crosshairs/Dot.Dot")));

	UPROPERTY(Config, EditAnywhere, Category = "Crosshair")
	float CrosshairScale = 1.0f;

	UFUNCTION()
	static UAimTrainerUserSettings* GetAimTrainerUserSettings();
};

