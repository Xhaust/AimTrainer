// Fill out your copyright notice in the Description page of Project Settings.


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