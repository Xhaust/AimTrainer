#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Settings/AimTrainerUserSettings.h"
#include "../Settings/GameProfileManager.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "SliderTextBox.h"
#include "GameSettingsMenu.generated.h"

UCLASS()
class AIMTRAINER_API UGameSettingsMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ProfileComboBox;
	
	// Sensitivity
	UPROPERTY(meta = (BindWidget))
	USliderTextBox* SensitivitySliderTextBox;

	UFUNCTION()
	void OnSensitivitySliderChanged(float NewValue);

	// FOV
	UPROPERTY(meta = (BindWidget))
	USliderTextBox* FOVSliderTextBox;

	UFUNCTION()
	void OnFOVSliderChanged(float NewValue);
	
	// Color Picker
	UPROPERTY(meta = (BindWidgetOptional))
	UButton* TargetColorPickerButton;
	
	UFUNCTION()
	void OnTargetColorPickerButtonClicked();

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* WallColorPickerButton;

	UFUNCTION()
	void OnWallColorPickerButtonClicked();

	// Backward-compatible binding for older widget blueprints.
	UPROPERTY(meta = (BindWidgetOptional))
	UButton* ColorPickerButton;
	

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