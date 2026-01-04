// Fill out your copyright notice in the Description page of Project Settings.


#include "MapRowWidget.h"
#include "MapEntry.h"
#include "AimTrainer/Gameplay/AimTrainerPlayerController.h"

void UMapRowWidget::Init(const FMapEntry& InMapEntry)
{
	MapEntry = InMapEntry;

	if (MapNameText)
	{
		MapNameText->SetText(FText::FromString(MapEntry.DisplayName));
	}
}

void UMapRowWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked);
	}
}

void UMapRowWidget::OnClicked()
{
	if (AAimTrainerPlayerController* PC = Cast<AAimTrainerPlayerController>(GetOwningPlayer()))
	{
		PC->LoadMap(MapEntry.MapName);
	}
}
