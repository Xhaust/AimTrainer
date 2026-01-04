#pragma once
#include "CoreMinimal.h"
#include "MapEntry.generated.h"

USTRUCT(BlueprintType)
struct FMapEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName MapName;

	UPROPERTY(BlueprintReadOnly)
	FString DisplayName;
};