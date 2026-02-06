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

	UPROPERTY()
	FString Rank;
};
