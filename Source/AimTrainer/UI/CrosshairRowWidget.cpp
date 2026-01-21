// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairRowWidget.h"
#include "CrosshairItem.h"

void UCrosshairRowWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UCrosshairItem* Item = Cast<UCrosshairItem>(ListItemObject);
	if (!Item) return;

	PreviewImage->SetBrushFromTexture(Item->PreviewTexture);
}
