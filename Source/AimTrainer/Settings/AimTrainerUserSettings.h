#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "AimTrainerUserSettings.generated.h"

UCLASS(Config=GameUserSettings)
class AIMTRAINER_API UAimTrainerUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	// ===== Video Settings =====
	
	// Resolution
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Resolution = FIntPoint(1920, 1080);
	
	// Fullscreen mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> WindowMode = EWindowMode::Fullscreen;

	// Quality
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OverallQuality = 3;

	// VSync
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bVSync = false;

	UPROPERTY(Config, EditDefaultsOnly, Category="Controls")
	FString CurrentGameProfile = "CS2";
	
	UPROPERTY(Config, EditDefaultsOnly, Category = "Controls")
	float MouseSensitivity = 1.0f;

	UPROPERTY(Config, EditDefaultsOnly, Category = "Controls")
	float FieldOfView = 90.0f;

	UPROPERTY(Config, EditAnywhere, Category = "Crosshair")
	TSoftObjectPtr<UTexture2D> CrosshairTexture = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(TEXT("/Game/Crosshairs/Dot.Dot")));

	UPROPERTY(Config, EditAnywhere, Category = "Crosshair")
	float CrosshairScale = 1.0f;

	UFUNCTION()
	static UAimTrainerUserSettings* GetAimTrainerUserSettings();
};

