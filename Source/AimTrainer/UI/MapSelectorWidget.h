// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "MapSelectorWidget.generated.h"

UCLASS()
class AIMTRAINER_API UMapSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UListView* MapList;

	UFUNCTION()
	void HandleMapSelected(UObject* Item);
};
