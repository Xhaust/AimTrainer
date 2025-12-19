// Fill out your copyright notice in the Description page of Project Settings.


#include "UserScores.h"

TArray<float> UUserScores::GetScoresForScenario(const FString& String)
{
	TArray<float> Result;
	for (const FScenarioScores& Scenario : ScenarioScores)
	{
		if (Scenario.ScenarioName == String)
		{
			Result.Reserve(Scenario.History.Num());
			for (const FScenarioScoreEntry& Entry : Scenario.History)
			{
				Result.Add(Entry.Score);
			}
			break;
		}
	}
	return Result;
}