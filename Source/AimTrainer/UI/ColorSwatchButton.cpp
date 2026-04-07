#include "ColorSwatchButton.h"

UColorSwatchButton::UColorSwatchButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OnClicked.AddDynamic(this, &ThisClass::HandleButtonClicked);
}

void UColorSwatchButton::HandleButtonClicked()
{
	OnSwatchColorClicked.Broadcast(SwatchColor);
}

