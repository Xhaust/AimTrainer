// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../UI/Crosshair.h"
#include "../UI/GameSettingsMenu.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "Weapon.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class AIMTRAINER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UFUNCTION()
	void ApplyFOV();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeapon* CurrentWeapon = nullptr;

	void Look(const FInputActionValue& Value);
	void StartFire();
	void StopFire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ToggleSettingsAction;
	
	UFUNCTION(BlueprintCallable)
	void ToggleSettingsMenu();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	TSubclassOf<UGameSettingsMenu> SettingsMenuClass;

	UPROPERTY()
	UGameSettingsMenu* SettingsMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair")
	TSubclassOf<UCrosshair> CrosshairClass;

	UPROPERTY()
	UCrosshair* Crosshair;

private:
	UPROPERTY()
	UAimTrainerUserSettings* Settings = nullptr;

	bool bIsSettingsOpen = false;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
