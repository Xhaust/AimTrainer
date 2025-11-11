// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AimTrainerUserSettings.h"
#include "GameProfileManager.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "GameSettingsMenu.generated.h"

UCLASS()
class AIMTRAINER_API UGameSettingsMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized()override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ProfileComboBox;
	
	UPROPERTY(meta = (BindWidget))
	class USlider* SensitivitySlider;

	UPROPERTY(meta = (BindWidget))
	class USlider* FOVSlider;

	UPROPERTY(meta = (BindWidget))
	class UButton* ApplyButton;

	UFUNCTION()
	void ApplyOnClicked();

private:
	UPROPERTY()
	UAimTrainerUserSettings* UserSettings;

	UPROPERTY()
	UGameProfileManager* ProfileManager;

}; 