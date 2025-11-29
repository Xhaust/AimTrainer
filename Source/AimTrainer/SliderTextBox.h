// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/EditableTextBox.h"
#include "SliderTextBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSettingValueChanged, float, NewValue);

UCLASS()
class AIMTRAINER_API USliderTextBox : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	USlider* Slider;
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBox;

	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnSettingValueChanged OnValueChanged;

	void SetValue(float NewValue);
	float GetValue();
	
	private:
	float CurrentValue = 0.0f;

	UFUNCTION()
	void HandleSliderChanged(float NewValue);

	UFUNCTION()
	void HandleTextBoxChanged(const FText& NewText);
};
