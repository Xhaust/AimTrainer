// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HUDWidget.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	EGameModeType CurrentMode = EGameModeType::Playground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode|Timer")
	float SessionDuration = 30.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Game Mode|Timer")
	float TimeRemaining = 0.f;

	UPROPERTY()
	FTimerUpdated OnTimerUpdated;

	UFUNCTION(BlueprintCallable)
	void StartSession();

	UFUNCTION()
	void TickSession();

	UFUNCTION(BlueprintCallable)
	void EndSession();

	UFUNCTION(BlueprintCallable)
	void HandleTargetDestroyed(ATarget* DestroyedTarget);

	void AddScore(int32 Points);
	
	UFUNCTION(BlueprintCallable)
	void ToggleGameMode();
	
private:
	FTimerHandle SessionTimerHandle;

	int32 PlayerScore = 0;

	UPROPERTY()
	UHUDWidget* HUDWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	
};
