// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../UI/HUDWidget.h"
#include "Target.h"
#include "AimTrainerGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimerUpdated, float, NewTime);

UENUM(BlueprintType)
enum class EGameModeType : uint8
{
	TimedSession UMETA(DisplayName = "Timed Session"),
	Playground   UMETA(DisplayName = "Playground"),
};

UCLASS()
class AIMTRAINER_API AAimTrainerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UPROPERTY()
	EGameModeType CurrentMode = EGameModeType::Playground;

	UPROPERTY(EditAnywhere)
	float SessionDuration = 30.0f;

	UPROPERTY()
	float TimeRemaining = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Scenario")
	FString CurrentScenarioName = TEXT("Tile Frenzy");

	UPROPERTY()
	FTimerUpdated OnTimerUpdated;

	UFUNCTION()
	void StartSession();

	UFUNCTION()
	void TickSession();

	UFUNCTION()
	void EndSession();

	UFUNCTION()
	void HandleTargetDestroyed(ATarget* DestroyedTarget);

	void AddScore(int32 Points);
	
	UFUNCTION()
	void ToggleGameMode();

	UFUNCTION()
	void SaveScore(const FString& ScenarioName, float Score);

	UFUNCTION()
	void ShowScoreboard();

private:
	FTimerHandle SessionTimerHandle;

	float PlayerScore = 0.f;

	UPROPERTY()
	UHUDWidget* HUDWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ScoreboardWidgetClass;

	UPROPERTY()
	UUserWidget* ScoreboardWidget;
};
