// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MapEntryObject.generated.h"

UCLASS()
class AIMTRAINER_API UMapEntryObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString LabelName;

	UPROPERTY(BlueprintReadOnly)
	FName LevelName;
	
};
