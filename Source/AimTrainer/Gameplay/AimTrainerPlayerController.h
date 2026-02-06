#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "InputAction.h"
#include "AimTrainer/UI/Crosshair.h"
#include "AimTrainer/UI/GameSettingsMenu.h"
#include "AimTrainer/UI/MainMenu.h"
#include "AimTrainer/UI/Scoreboard.h"
#include "GameFramework/PlayerController.h"
#include "AimTrainerPlayerController.generated.h"

UCLASS()
class AIMTRAINER_API AAimTrainerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ApplyFOV();
	
	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenSettingsMenu();

	UFUNCTION()
	void OpenMapSelector();

	UFUNCTION()
	void OpenCrosshairSelector();

	UFUNCTION()
	void OpenScoreboard();

	UFUNCTION()
	void LoadMap(FName LevelName);

	UFUNCTION()
	void CloseAllMenus();

	UFUNCTION()
	void ApplyCrosshairFromFile(const FString& FilePath);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	// ===== Input =====
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* ToggleMenuAction;

	void HandleLook(const FInputActionValue& Value);
	void HandleStartFire();
	void HandleStopFire();
	void HandleEscape();

	// ===== UI =====

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMainMenu> MainMenuClass;
	
	UPROPERTY()
	UMainMenu* MainMenu;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UGameSettingsMenu> SettingsMenuClass;
	
	UPROPERTY()
	UGameSettingsMenu* SettingsMenu;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMapSelectorWidget> MapSelectorClass;
	
	UPROPERTY()
	UMapSelectorWidget* MapSelector;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UCrosshairSelectorWidget> CrosshairSelectorClass;

	UPROPERTY()
	UCrosshairSelectorWidget* CrosshairSelector;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UScoreboard> ScoreboardClass;
	
	UPROPERTY()
	UScoreboard* Scoreboard;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UCrosshair> CrosshairClass;

	UPROPERTY()
	UCrosshair* Crosshair;

	UFUNCTION()
	bool AnyMenuOpen() const;

	// ===== Settings =====
	UPROPERTY()
	UAimTrainerUserSettings* UserSettings;
};
