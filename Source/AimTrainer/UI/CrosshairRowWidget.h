#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "CrosshairItem.h"
#include "CrosshairRowWidget.generated.h"

UCLASS()
class AIMTRAINER_API UCrosshairRowWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UPROPERTY(meta = (BindWidget))
	UImage* PreviewImage;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UFUNCTION()
	void OnClicked();

private:
	UPROPERTY()
	UCrosshairItem* CrosshairItem;
};
