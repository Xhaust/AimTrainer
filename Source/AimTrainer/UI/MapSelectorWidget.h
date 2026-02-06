#pragma once

#include "CoreMinimal.h"
#include "MapRowWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "MapSelectorWidget.generated.h"

UCLASS()
class AIMTRAINER_API UMapSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MapListBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMapRowWidget> MapRowClass;

	void PopulateMaps();
};
