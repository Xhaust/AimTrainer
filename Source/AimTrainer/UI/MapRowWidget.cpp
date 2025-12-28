// Fill out your copyright notice in the Description page of Project Settings.


#include "MapRowWidget.h"
#include "MapEntryObject.h"

void UMapRowWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	const UMapEntryObject* Entry = Cast<UMapEntryObject>(ListItemObject);
	if (!Entry || !MapNameText) return;

	MapNameText->SetText(FText::FromString(Entry->LabelName));
}
