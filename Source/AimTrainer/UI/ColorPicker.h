#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/WrapBox.h"
#include "ColorPicker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnColorSelectedSignature, FLinearColor, SelectedColor);

UCLASS()
class AIMTRAINER_API UColorPicker : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Color Picker")
	FOnColorSelectedSignature OnColorSelected;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* ColorGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLinearColor> Palette = {
		FLinearColor::Black, FLinearColor::White, FLinearColor::Red, FLinearColor::Green, FLinearColor::Blue
	};
	
	UPROPERTY(meta = (BindWidget))
	UEditableText* HexText;
	
	UFUNCTION()
	void OnColorButtonClicked(FLinearColor Color);

	UFUNCTION()
	static FLinearColor ParseHexColor(const FString& HexString);

	UFUNCTION()
	static FString ToHex(const FLinearColor& Color);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnSwatchColorClicked(FLinearColor SelectedColor);
};
