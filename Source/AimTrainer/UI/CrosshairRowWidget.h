// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CrosshairRowWidget.generated.h"

UCLASS()
class AIMTRAINER_API UCrosshairRowWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* PreviewImage;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
};
