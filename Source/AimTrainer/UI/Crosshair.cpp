// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Modules/ModuleManager.h"
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
UTexture2D* LoadTextureFromFile(const FString& FilePath)
{
	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
	{
		return nullptr;
	}

	IImageWrapperModule& ImageWrapperModule =
		FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");

	EImageFormat Format = ImageWrapperModule.DetectImageFormat(
		FileData.GetData(), FileData.Num());

	if (Format == EImageFormat::Invalid)
	{
		return nullptr;
	}

	TSharedPtr<IImageWrapper> Wrapper =
		ImageWrapperModule.CreateImageWrapper(Format);

	if (!Wrapper->SetCompressed(FileData.GetData(), FileData.Num()))
	{
		return nullptr;
	}

	TArray<uint8> RawData;
	if (!Wrapper->GetRaw(ERGBFormat::BGRA, 8, RawData))
	{
		return nullptr;
	}

	UTexture2D* Texture =
		UTexture2D::CreateTransient(
			Wrapper->GetWidth(),
			Wrapper->GetHeight(),
			PF_B8G8R8A8
		);

	if (!Texture) return nullptr;

	void* TextureData =
		Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);

	FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());

	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
	Texture->UpdateResource();

	return Texture;
}
