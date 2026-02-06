#pragma once

#include "CoreMinimal.h"
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

	FScenarioScoreEntry() = default;
	FScenarioScoreEntry(float InScore, const FString& InDate)
		: Score(InScore), Date(InDate)
	{}
	
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

	TArray<float> GetScoresForScenario(const FString& String);

	TArray<FScenarioScoreEntry> GetEntriesForScenario(const FString& ScenarioName);
};
