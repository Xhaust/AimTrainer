// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AimTrainerUserSettings.h"
#include "GameProfileManager.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "GameSettingsMenu.generated.h"

UCLASS()
class AIMTRAINER_API UGameSettingsMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized()override;
	virtual void NativeConstruct() override;
	void BindTextBoxToSlider(USlider* Slider, UEditableTextBox* TextBox);

public:
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ProfileComboBox;
	
	// Sensitivity
	UPROPERTY(meta = (BindWidget))
	USlider* SensitivitySlider;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* SensitivityTextBox;

	UPROPERTY(meta = (BindWidget))
	USlider* FOVSlider;

	UPROPERTY(meta = (BindWidget))
	UButton* ApplyButton;

	UFUNCTION()
	void ApplyOnClicked();

private:
	UPROPERTY()
	UAimTrainerUserSettings* UserSettings;

	UPROPERTY()
	UGameProfileManager* ProfileManager;

}; 