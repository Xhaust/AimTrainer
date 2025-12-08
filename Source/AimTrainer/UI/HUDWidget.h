// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HUDWidget.generated.h"


UCLASS()
class AIMTRAINER_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateTimer(int32 Seconds);

	UFUNCTION(BlueprintCallable)
	void UpdateScore(int32 NewScore);

	UFUNCTION(BlueprintCallable)
	void UpdateGameModeText(const FString& NewMode);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameModeText;
	
};
