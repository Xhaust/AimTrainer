#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Crosshair.generated.h"

UCLASS()
class AIMTRAINER_API UCrosshair : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCrosshairTexture(UTexture2D* NewTexture);
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairImage;
};
