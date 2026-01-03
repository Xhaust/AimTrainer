// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
#include "AimTrainer/UI/Crosshair.h"
#include "AimTrainer/UI/GameSettingsMenu.h"
#include "GameFramework/PlayerController.h"
#include "AimTrainerPlayerController.generated.h"

UCLASS()
class AIMTRAINER_API AAimTrainerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ApplyFOV();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	// ===== Input =====
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* ToggleSettingsAction;

	void HandleLook(const FInputActionValue& Value);
	void HandleStartFire();
	void HandleStopFire();
	void HandleEscape();

	// ===== UI =====
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UGameSettingsMenu> SettingsMenuClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UCrosshair> CrosshairClass;

	UPROPERTY()
	UGameSettingsMenu* SettingsMenu;

	UPROPERTY()
	UCrosshair* Crosshair;

	bool bSettingsOpen = false;

	void OpenSettingsMenu();
	void CloseSettingsMenu();

	// ===== Settings =====
	UPROPERTY()
	UAimTrainerUserSettings* UserSettings;
};
