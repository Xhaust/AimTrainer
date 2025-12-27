// Fill out your copyright notice in the Description page of Project Settings.


#include "MapSelectorWidget.h"

#include "MapEntryObject.h"
#include "AimTrainer/Gameplay/AimTrainerGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UMapSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!MapList) return;

	MapList->ClearListItems();
	MapList->OnItemClicked().AddUObject(this, &UMapSelectorWidget::HandleMapSelected);

	if (UAimTrainerGameInstance* GI =
		GetWorld()->GetGameInstance<UAimTrainerGameInstance>())
	{
		for (const FMapInfo& Map : GI->AvailableMaps)
		{
			UMapEntryObject* Entry = NewObject<UMapEntryObject>(this);
			Entry->LabelName = Map.LabelName;
			Entry->LevelName = Map.LevelName;

			MapList->AddItem(Entry);
		}
	}
}

void UMapSelectorWidget::HandleMapSelected(UObject* Item)
{
	UMapEntryObject* Entry = Cast<UMapEntryObject>(Item);
	if (!Entry) return;

	UGameplayStatics::OpenLevel(this, Entry->LevelName);
}