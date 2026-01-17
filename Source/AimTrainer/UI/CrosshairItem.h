// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CrosshairItem.generated.h"

UCLASS()
class AIMTRAINER_API UCrosshairItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString FileName;

	UPROPERTY(BlueprintReadOnly)
	FString FullPath;

	UPROPERTY(BlueprintReadOnly)
	UTexture2D* PreviewTexture;
};
