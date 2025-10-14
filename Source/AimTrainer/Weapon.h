// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class AIMTRAINER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartFire();
	void StopFire();

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Damage = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float FireRate = 0.1f;

	bool bIsFiring = false;
	bool bAutomatic = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
