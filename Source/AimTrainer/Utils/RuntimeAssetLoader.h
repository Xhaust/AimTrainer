#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RuntimeAssetLoader.generated.h"

UCLASS()
class AIMTRAINER_API URuntimeAssetLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UTexture2D* LoadTextureFromFile(const FString& FilePath);
};
