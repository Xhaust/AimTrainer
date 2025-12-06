// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATarget::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float HealthBeforeDamage = CurrentHealth;
	
	CurrentHealth -= FMath::Min(CurrentHealth, DamageAmount);	
	if (CurrentHealth <= 0.0f)
	{
		Destroy();
		OnTargetDestroyed.Broadcast(this);
	}

	return HealthBeforeDamage - CurrentHealth;
}

