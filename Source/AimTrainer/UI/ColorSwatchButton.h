#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "ColorSwatchButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwatchColorClickedSignature, FLinearColor, SelectedColor);

UCLASS()
class AIMTRAINER_API UColorSwatchButton : public UButton
{
	GENERATED_BODY()

public:
	UColorSwatchButton(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Picker")
	FLinearColor SwatchColor = FLinearColor::White;

	UPROPERTY(BlueprintAssignable, Category = "Color Picker")
	FOnSwatchColorClickedSignature OnSwatchColorClicked;

private:
	UFUNCTION()
	void HandleButtonClicked();
};

