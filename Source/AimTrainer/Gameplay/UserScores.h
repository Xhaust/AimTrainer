// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AimTrainer/UI/Scoreboard.h"
#include "GameFramework/SaveGame.h"
#include "UserScores.generated.h"

USTRUCT(BlueprintType)
struct FScenarioScoreEntry
{
	GENERATED_BODY()

	UPROPERTY()
	float Score = .0f;

	UPROPERTY()
	FString Date;

	FScenarioScoreEntry() {}

	FScenarioScoreEntry(float InScore)
		: Score(InScore)
	{
		Date = FDateTime::Now().ToIso8601();
	}
	
};

USTRUCT(BlueprintType)
struct FScenarioScores
{
	GENERATED_BODY()

	UPROPERTY()
	FString ScenarioName;

	UPROPERTY()
	TArray<FScenarioScoreEntry> History;
	
	UPROPERTY()
	float HighScore = .0f;

	FScenarioScores() {}

	FScenarioScores(const FString& InScenarioName)
		: ScenarioName(InScenarioName)
	{}
};

UCLASS()
class AIMTRAINER_API UUserScores : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FScenarioScores> ScenarioScores;

	TArray<float>* GetScoresForScenario(const FString& String);
};
