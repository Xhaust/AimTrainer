#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/WrapBox.h"
#include "ColorPicker.generated.h"

UCLASS()
class AIMTRAINER_API UColorPicker : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UWrapBox* ColorGrid;

	UPROPERTY(meta = (BindWidget))
	UEditableText* ColorPickedText;
	
	UFUNCTION()
	void OnColorButtonClicked(FLinearColor Color);
};
