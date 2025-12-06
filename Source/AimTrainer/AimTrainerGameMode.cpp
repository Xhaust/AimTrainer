// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrainerGameMode.h"

void AAimTrainerGameMode::BeginPlay()
{
	Super::BeginPlay();

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
}

void AAimTrainerGameMode::TickSession()
{
	TimeRemaining -= 1.0f;

	if (TimeRemaining <= 0.f)
	{
		EndSession();
	}
	OnTimerUpdated.Broadcast(TimeRemaining);
}