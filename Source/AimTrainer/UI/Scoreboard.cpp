// Fill out your copyright notice in the Description page of Project Settings.


#include "Scoreboard.h"
#include "ScoreRow.h"
#include "ScoreRowWidget.h"
#include "AimTrainer/Gameplay/AimTrainerGameInstance.h"
#include "AimTrainer/Gameplay/UserScores.h"
#include "Kismet/GameplayStatics.h"

void UScoreboard::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UserScores = Cast<UUserScores>(UGameplayStatics::LoadGameFromSlot(TEXT("UserScores"), 0));

	if (UAimTrainerGameInstance* GI = GetGameInstance<UAimTrainerGameInstance>())
	{
		SetScenarioName(GI->GetCurrentMapName());
	}
}

void UScoreboard::SetScenarioName(const FString& ScenarioName)
{
	if (ScenarioName.IsEmpty())
	{
		return;
	}

	CurrentScenarioName = ScenarioName;

	if (ScenarioNameText)
	{
		ScenarioNameText->SetText(FText::FromString(ScenarioName));
	}

	UpdateScoreboard();
}


static FString GetRankFromScoreForScenario(const FString& ScenarioName, float Score)
{
	// TileFrenzy (hard)
	if (ScenarioName.Equals(TEXT("TileFrenzy"), ESearchCase::IgnoreCase))
	{
		if (Score >= 180.f) return TEXT("SS");
		if (Score >= 160.f) return TEXT("S");
		if (Score >= 150.f) return TEXT("A");
		if (Score >= 90.f) return TEXT("B");
		if (Score >= 50.f)  return TEXT("C");
		return TEXT("D");
	}

	// 1wall6targets (small/fast)
	if (ScenarioName.Equals(TEXT("1wall6targets"), ESearchCase::IgnoreCase))
	{
		if (Score >= 80.f) return TEXT("SS");
		if (Score >= 75.f) return TEXT("S");
		if (Score >= 65.f) return TEXT("A");
		if (Score >= 55.f)  return TEXT("B");
		if (Score >= 40.f)  return TEXT("C");
		return TEXT("D");
	}

	// GroundPlaza (medium)
	if (ScenarioName.Equals(TEXT("GroundPlaza"), ESearchCase::IgnoreCase))
	{
		if (Score >= 1000.f) return TEXT("SS");
		if (Score >= 900.f) return TEXT("S");
		if (Score >= 800.f) return TEXT("A");
		if (Score >= 600.f) return TEXT("B");
		if (Score >= 400.f)  return TEXT("C");
		return TEXT("D");
	}

	// Default thresholds (fallback)
	if (Score >= 200.f) return TEXT("SS");
	if (Score >= 150.f) return TEXT("S");
	if (Score >= 100.f) return TEXT("A");
	if (Score >= 80.f) return TEXT("B");
	if (Score >= 50.f)  return TEXT("C");
	return TEXT("D");
}

void UScoreboard::UpdateScoreboard()
{
	if (!UserScores || !ScoreListView || CurrentScenarioName.IsEmpty())
	{
		if (RankText)
		{
			RankText->SetText(FText::FromString(TEXT("N/A")));
		}
		return;
	}

	ScoreListView->ClearListItems();

	TArray<FScenarioScoreEntry> Entries = UserScores->GetEntriesForScenario(CurrentScenarioName);

	if (Entries.Num() == 0)
	{
		if (RankText)
		{
			RankText->SetText(FText::FromString(TEXT("N/A")));
		}
		return;
	}

	// sort descending so highest score is first
	Entries.Sort([](const FScenarioScoreEntry& A, const FScenarioScoreEntry& B)
	{
		return A.Score > B.Score;
	});

	const float HighestScore = Entries[0].Score;
	const FString RankString = GetRankFromScoreForScenario(CurrentScenarioName, HighestScore);

	if (RankText)
	{
		RankText->SetText(FText::FromString(RankString));
	}

	for (const FScenarioScoreEntry& Entry : Entries)
	{
		UScoreRow* ScoreItem = NewObject<UScoreRow>(this);
		ScoreItem->Score = Entry.Score;
		ScoreItem->Date = Entry.Date;
		ScoreItem->Rank = GetRankFromScoreForScenario(CurrentScenarioName, Entry.Score);
		ScoreListView->AddItem(ScoreItem);
	}
}