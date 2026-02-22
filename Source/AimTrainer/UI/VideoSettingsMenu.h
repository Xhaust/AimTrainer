#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "VideoSettingsMenu.generated.h"

UCLASS()
class AIMTRAINER_API UVideoSettingsMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ResolutionCombo;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* WindowModeCombo;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* QualityCombo;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* VSyncCheckBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ApplyButton;

	UFUNCTION()
	void OnApplyClicked();
};
