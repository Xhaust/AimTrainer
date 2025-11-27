// Fill out your copyright notice in the Description page of Project Settings.


#include "SliderTextBox.h"

void USliderTextBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (Slider && TextBox)
	{
		Slider->OnValueChanged.AddDynamic(this, &USliderTextBox::HandleSliderChanged);
		TextBox->OnTextChanged.AddDynamic(this, &USliderTextBox::HandleTextBoxChanged);
	}
}

float USliderTextBox::GetValue()
{
	return CurrentValue;
}

void USliderTextBox::SetValue(float NewValue)
{
	CurrentValue = FMath::Clamp(NewValue, MinValue, MaxValue);

	if (Slider)
	{
		Slider->SetValue(CurrentValue);
	}

	if (TextBox)
	{
		TextBox->SetText(FText::AsNumber(CurrentValue));
	}
}

void USliderTextBox::HandleSliderChanged(float NewValue)
{
	if (TextBox)
	{
		TextBox->SetText(FText::AsNumber(NewValue));
	}
}

void USliderTextBox::HandleTextBoxChanged(const FText& NewText)
{
	if (Slider)
	{
		float NewValue = FCString::Atof(*NewText.ToString());
		Slider->SetValue(NewValue);
	}
}