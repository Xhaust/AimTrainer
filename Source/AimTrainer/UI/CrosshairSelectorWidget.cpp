
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
	if (!CrosshairList) return;

	CrosshairList->ClearListItems();

	const FString Dir = FPaths::ProjectSavedDir() / TEXT("Crosshairs");

	TArray<FString> Files;
	IFileManager::Get().FindFiles(Files, *Dir, TEXT("*.png"));

	for (const FString& File : Files)
	{
		UCrosshairItem* Item = NewObject<UCrosshairItem>(this);

		Item->FileName = File;
		Item->FullPath = Dir / File;
		Item->PreviewTexture = URuntimeAssetLoader::LoadTextureFromFile(Item->FullPath);

		CrosshairList->AddItem(Item);
	}
}