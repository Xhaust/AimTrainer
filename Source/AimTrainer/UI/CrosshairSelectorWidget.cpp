
#include "CrosshairSelectorWidget.h"
#include "CrosshairItem.h"
#include "AimTrainer/Utils/RuntimeAssetLoader.h"

void UCrosshairSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	LoadCrosshairs();

	if (OpenDirectoryButton)
	{
		OpenDirectoryButton->OnClicked.AddDynamic(this, &ThisClass::OnOpenDirectoryClicked);
	}

	if (RefreshButton)
	{
		RefreshButton->OnClicked.AddDynamic(this, &ThisClass::LoadCrosshairs);
	}
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

void UCrosshairSelectorWidget::OnOpenDirectoryClicked()
{
	const FString Dir = FPaths::ProjectSavedDir() / TEXT("Crosshairs");
	IFileManager::Get().MakeDirectory(*Dir, true);
	const FString AbsoluteDir = FPaths::ConvertRelativePathToFull(Dir);
	FPlatformProcess::ExploreFolder(*AbsoluteDir);
}