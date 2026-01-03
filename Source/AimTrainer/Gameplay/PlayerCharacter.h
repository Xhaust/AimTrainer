// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Weapon.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class AIMTRAINER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void Look(const FInputActionValue& Value);
	void StartFire();
	void StopFire();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY()
	AWeapon* CurrentWeapon = nullptr;
};
