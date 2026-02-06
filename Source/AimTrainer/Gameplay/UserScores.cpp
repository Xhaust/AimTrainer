
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

TArray<FScenarioScoreEntry> UUserScores::GetEntriesForScenario(const FString& ScenarioName)
{
	TArray<FScenarioScoreEntry> Result;
	for (const FScenarioScores& Scenario : ScenarioScores)
	{
		if (Scenario.ScenarioName == ScenarioName)
		{
			Result = Scenario.History; // copy the entries (score + date)
			break;
		}
	}
	return Result;
}