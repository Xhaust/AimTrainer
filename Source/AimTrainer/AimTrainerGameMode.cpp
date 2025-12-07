// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrainerGameMode.h"
#include "HUDWidget.h"

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
		PlayerScore = 0;

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
	PlayerScore = 0;
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
	AddScore(1);
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