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

	UserScores = Cast<UUserScores>(
		UGameplayStatics::LoadGameFromSlot(TEXT("UserScores"), 0)
	);

	if (UAimTrainerGameInstance* GI = GetGameInstance<UAimTrainerGameInstance>())
	{
		SetScenarioName(GI->CurrentScenarioName);
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

void UScoreboard::UpdateScoreboard()
{
	if (!UserScores || !ScoreListView || CurrentScenarioName.IsEmpty())
	{
		return;
	}

	ScoreListView->ClearListItems();

	TArray<float> Scores =
		UserScores->GetScoresForScenario(CurrentScenarioName);

	for (float Score : Scores)
	{
		UScoreRow* ScoreItem = NewObject<UScoreRow>(this);
		ScoreItem->Score = Score;

		ScoreListView->AddItem(ScoreItem);
	}
}