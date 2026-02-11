
#include "CrosshairSelectorWidget.h"
#include "CrosshairItem.h"
#include "AimTrainer/Utils/RuntimeAssetLoader.h"

void UCrosshairSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	LoadCrosshairs();
}

void UCrosshairSelectorWidget::LoadCrosshairs()
{
	if (!CrosshairTileView) return;

	CrosshairTileView->ClearListItems();

	const FString Dir = FPaths::ProjectSavedDir() / TEXT("Crosshairs");

	TArray<FString> Files;
	IFileManager::Get().FindFiles(Files, *Dir, TEXT("*.png"));

	for (const FString& File : Files)
	{
		UCrosshairItem* Item = NewObject<UCrosshairItem>(this);

		Item->FileName = File;
		Item->FullPath = Dir / File;
		URuntimeAssetLoader* Loader = NewObject<URuntimeAssetLoader>(this);
		Item->PreviewTexture = Loader ? Loader->LoadTextureFromFile(Item->FullPath) : nullptr;

		CrosshairTileView->AddItem(Item);
	}
}