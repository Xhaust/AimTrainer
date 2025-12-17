// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrainerGameMode.h"
#include "UserScores.h"
#include "../UI/HUDWidget.h"
#include "AimTrainer/UI/Scoreboard.h"
#include "Kismet/GameplayStatics.h"

void AAimTrainerGameMode::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
	if (HUDWidget)
		HUDWidget->AddToViewport();

	if (CurrentMode == EGameModeType::TimedSession)
	{
		StartSession();
	}
}

void AAimTrainerGameMode::StartSession()
{
	if (CurrentMode == EGameModeType::TimedSession)
	{
		TimeRemaining = SessionDuration;
		PlayerScore = 0.f;

		GetWorldTimerManager().SetTimer(
			SessionTimerHandle,
			this,
			&AAimTrainerGameMode::TickSession,
			1.0f,
			true
		);
	}
}

void AAimTrainerGameMode::EndSession()
{
	GetWorldTimerManager().ClearTimer(SessionTimerHandle);

	if (CurrentMode == EGameModeType::TimedSession)
	{
		SaveScore(CurrentScenarioName, PlayerScore);
		ShowScoreboard();
	}
	
	PlayerScore = 0.0f;
}

void AAimTrainerGameMode::TickSession()
{
	TimeRemaining -= 1.0f;
	
	if (HUDWidget)
		HUDWidget->UpdateTimer(TimeRemaining);
	
	if (TimeRemaining <= 0.f)
	{
		EndSession();
	}
	OnTimerUpdated.Broadcast(TimeRemaining);
}

void AAimTrainerGameMode::HandleTargetDestroyed(ATarget* DestroyedTarget)
{
	AddScore(1.0f);
}

void AAimTrainerGameMode::AddScore(int32 Points)
{
	PlayerScore += Points;
	if (HUDWidget)
	{
		HUDWidget->UpdateScore(PlayerScore);
	}
}

void AAimTrainerGameMode::ToggleGameMode()
{
	if (CurrentMode == EGameModeType::TimedSession)
	{
		CurrentMode = EGameModeType::Playground;
		EndSession();
		if (HUDWidget)
		{
			HUDWidget->UpdateGameModeText(TEXT("Playground"));
		}
	}
	else
	{
		CurrentMode = EGameModeType::TimedSession;
		StartSession();
		if (HUDWidget)
		{
			HUDWidget->UpdateGameModeText(TEXT("Timed Session"));
		}
	}
}

void AAimTrainerGameMode::SaveScore(
	const FString& ScenarioName,
	float Score)
{
	UUserScores* Save =
		Cast<UUserScores>(UGameplayStatics::LoadGameFromSlot(TEXT("UserScores"), 0));

	if (!Save)
	{
		Save = Cast<UUserScores>(
			UGameplayStatics::CreateSaveGameObject(UUserScores::StaticClass()));
	}

	FScenarioScores* Scenario = Save->ScenarioScores.FindByPredicate(
		[&](const FScenarioScores& S)
		{
			return S.ScenarioName == ScenarioName;
		}
	);

	if (!Scenario)
	{
		Save->ScenarioScores.Add(FScenarioScores(ScenarioName));
		Scenario = &Save->ScenarioScores.Last();
	}

	Scenario->History.Add(FScenarioScoreEntry(Score));
	Scenario->HighScore = FMath::Max(Scenario->HighScore, Score);

	UGameplayStatics::SaveGameToSlot(Save, TEXT("UserScores"), 0);
}

void AAimTrainerGameMode::ShowScoreboard()
{
	if (!ScoreboardWidgetClass) return;

	if (!ScoreboardWidget)
	{
		ScoreboardWidget = CreateWidget<UUserWidget>(
			GetWorld(),
			ScoreboardWidgetClass
		);
	}

	if (ScoreboardWidget)
	{

		if (UScoreboard* SB = Cast<UScoreboard>(ScoreboardWidget))
		{
			SB->SetScenarioName(CurrentScenarioName);
		}
		
		ScoreboardWidget->AddToViewport();

		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->SetShowMouseCursor(true);
			PC->SetInputMode(FInputModeUIOnly());
		}
	}
}