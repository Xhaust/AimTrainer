// Fill out your copyright notice in the Description page of Project Settings.


#include "MapSelectorWidget.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "MapEntry.h"

void UMapSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	PopulateMaps();
}

void UMapSelectorWidget::PopulateMaps()
{
	if (!MapListBox || !MapRowClass) return;

	MapListBox->ClearChildren();

	FAssetRegistryModule& AssetRegistry =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	FARFilter Filter;
	Filter.ClassPaths.Add(UWorld::StaticClass()->GetClassPathName());
	Filter.PackagePaths.Add(FName("/Game/Maps"));
	Filter.bRecursivePaths = true;

	TArray<FAssetData> Maps;
	AssetRegistry.Get().GetAssets(Filter, Maps);

	for (const FAssetData& Asset : Maps)
	{
		FMapEntry Entry;
		Entry.MapName = Asset.AssetName;
		Entry.DisplayName = Asset.AssetName.ToString();

		UMapRowWidget* Row = CreateWidget<UMapRowWidget>(this, MapRowClass);
		if (Row)
		{
			Row->Init(Entry);
			MapListBox->AddChild(Row);
		}
	}
}