// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreRowWidget.h"
#include "ScoreRow.h"

void UScoreRowWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UScoreRow* Data = Cast<UScoreRow>(ListItemObject);
	if (!Data) return;

	ScoreText->SetText(FText::AsNumber(Data->Score));
	DateText->SetText(FText::FromString(Data->Date));
}