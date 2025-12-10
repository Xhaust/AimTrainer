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

	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY()
	AWeapon* CurrentWeapon = nullptr;

	void Look(const FInputActionValue& Value);
	void StartFire();
	void StopFire();

	UPROPERTY(EditDefaultsOnly)
	UInputAction* ToggleSettingsAction;
	
	UFUNCTION()
	void ToggleSettingsMenu();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameSettingsMenu> SettingsMenuClass;

	UPROPERTY()
	UGameSettingsMenu* SettingsMenu;

	UPROPERTY(EditDefaultsOnly)
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
