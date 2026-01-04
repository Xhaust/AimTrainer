// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSettingsMenu.h"
#include "MapSelectorWidget.h"
#include "Scoreboard.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

UCLASS()
class AIMTRAINER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override; 
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* StartEndGameButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StartEndGameText;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnStartGameClicked();
	
	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UGameSettingsMenu> SettingsMenuClass;

	UPROPERTY()
	UGameSettingsMenu* SettingsMenu;

	UFUNCTION()
	void OnSettingsMenuClicked();

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMapSelectorWidget> MapSelectorClass;

	UPROPERTY()
	UMapSelectorWidget* MapSelector;

	UPROPERTY(meta = (BindWidget))
	UButton* MapSelectorButton;

	UFUNCTION()
	void OnMapSelectorClicked();
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UScoreboard> ScoreboardWidgetClass;

	UPROPERTY()
	UScoreboard* ScoreboardWidget;

	UPROPERTY(meta = (BindWidget))
	UButton* ScoreboardButton;

	UFUNCTION()
	void OnShowScoreboardClicked();
};
