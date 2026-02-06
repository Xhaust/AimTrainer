
#include "CrosshairRowWidget.h"
#include "CrosshairItem.h"
#include "AimTrainer/Gameplay/AimTrainerPlayerController.h"

void UCrosshairRowWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnClicked);
	}
}

void UCrosshairRowWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UCrosshairItem* Item = Cast<UCrosshairItem>(ListItemObject);
	if (!Item) return;

	PreviewImage->SetBrushFromTexture(Item->PreviewTexture);
}

void UCrosshairRowWidget::OnClicked()
{
	if (!CrosshairItem) return;

	if (AAimTrainerPlayerController* PC =
		Cast<AAimTrainerPlayerController>(GetOwningPlayer()))
	{
		PC->ApplyCrosshairFromFile(CrosshairItem->FullPath);
	}
}
