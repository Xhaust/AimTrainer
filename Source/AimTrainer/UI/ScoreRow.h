// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreRow.generated.h"

UCLASS()
class AIMTRAINER_API UScoreRow : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	float Score;

	UPROPERTY()
	FString Date;
};
