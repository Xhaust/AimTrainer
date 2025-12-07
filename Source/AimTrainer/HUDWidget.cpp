// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::UpdateTimer(int32 Seconds)
{
	if (TimerText)
		TimerText->SetText(FText::AsNumber(Seconds));
}

void UHUDWidget::UpdateScore(int32 NewScore)
{
	if (ScoreText)
		ScoreText->SetText(FText::AsNumber(NewScore));
}

void UHUDWidget::UpdateGameModeText(const FString& NewMode)
{
	if (GameModeText)
		GameModeText->SetText(FText::FromString(NewMode));
}