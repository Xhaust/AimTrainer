#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "CrosshairSelectorWidget.generated.h"

UCLASS()
class AIMTRAINER_API UCrosshairSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UListView* CrosshairList;

	void LoadCrosshairs();
};
