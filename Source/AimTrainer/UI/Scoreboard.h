// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AimTrainer/Gameplay/UserScores.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Scoreboard.generated.h"

UCLASS()
class AIMTRAINER_API UScoreboard : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScenarioNameText;

	UPROPERTY(meta = (BindWidget))
	UListView* ScoreListView;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RankText;

	void SetScenarioName(const FString& ScenarioName);

private:
	FString CurrentScenarioName;
	
	UPROPERTY()
	UUserScores* UserScores;

	void UpdateScoreboard();
};
