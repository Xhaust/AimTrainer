#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "CrosshairSelectorWidget.generated.h"

UCLASS()
class AIMTRAINER_API UCrosshairSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UListView* CrosshairTileView;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OpenDirectoryButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* RefreshButton;

	UFUNCTION()
	void OnOpenDirectoryClicked();

	UFUNCTION()
	void OnRefreshClicked();

	void LoadCrosshairs();
};
