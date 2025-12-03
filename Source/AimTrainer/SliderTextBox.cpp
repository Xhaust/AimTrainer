// Fill out your copyright notice in the Description page of Project Settings.


#include "SliderTextBox.h"

void USliderTextBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (Text)
	{
		Text->SetText(LabelText);
	}

	if (Slider && TextBox)
	{
		Slider->SetMinValue(MinValue);
		Slider->SetMaxValue(MaxValue);
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
	CurrentValue = FMath::Clamp(NewValue, MinValue, MaxValue);
	if (TextBox)
	{
		TextBox->SetText(FText::AsNumber(CurrentValue));
	}
	UE_LOG(LogTemp, Verbose, TEXT("SliderTextBox: broadcasting NewValue=%f"), CurrentValue);
	OnValueChanged.Broadcast(CurrentValue);
}

void USliderTextBox::HandleTextBoxChanged(const FText& NewText)
{
	float NewValue = FCString::Atof(*NewText.ToString());
	CurrentValue = FMath::Clamp(NewValue, MinValue, MaxValue);
	if (Slider)
	{
		Slider->SetValue(CurrentValue);
	}
	UE_LOG(LogTemp, Verbose, TEXT("SliderTextBox: broadcasting NewValue=%f"), CurrentValue);
	OnValueChanged.Broadcast(CurrentValue);
}