// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapEntry.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MapRowWidget.generated.h"

UCLASS()
class AIMTRAINER_API UMapRowWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	void Init(const FMapEntry& InMapEntry);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MapNameText;

	UFUNCTION()
	void OnClicked();

private:
	FMapEntry MapEntry;
};
