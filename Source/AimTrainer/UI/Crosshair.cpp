
#include "Crosshair.h"
#include "../Settings/AimTrainerUserSettings.h"

void UCrosshair::NativeConstruct()
{
	Super::NativeConstruct();

	UAimTrainerUserSettings* Settings = UAimTrainerUserSettings::GetAimTrainerUserSettings();
	if (Settings && CrosshairImage)
	{
		UTexture2D* Texture = Settings->CrosshairTexture.Get();
		if (Texture)
			CrosshairImage->SetBrushFromTexture(Texture);
			CrosshairImage->SetRenderScale(FVector2D(Settings->CrosshairScale));
	}
}

void UCrosshair::SetCrosshairTexture(UTexture2D* NewTexture)
{
	if (!CrosshairImage || !NewTexture) return;

	CrosshairImage->SetBrushFromTexture(NewTexture, true);

	if (UAimTrainerUserSettings* Settings = UAimTrainerUserSettings::GetAimTrainerUserSettings())
	{
		Settings->CrosshairTexture = NewTexture;
		Settings->SaveConfig();
	}
}