// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UserScores.generated.h"

USTRUCT(BlueprintType)
struct FScenarioScore
{
	GENERATED_BODY()

	UPROPERTY()
	FString ScenarioName;

	UPROPERTY()
	float HighScore = .0f;

	UPROPERTY()
	float LastScore = .0f;
};
UCLASS()
class AIMTRAINER_API UUserScores : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FScenarioScore> ScenarioScores;
};
