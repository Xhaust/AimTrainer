// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::StartFire()
{
	if (bAutomatic)
	{
		// Fire repeatedly using a timer
		GetWorldTimerManager().SetTimer(
			FireTimer,
			this,
			&AWeapon::FireShot,
			FireRate,
			true,
			0.0f
		);
	}
	else
	{
		// Fire only once (semi-auto)
		FireShot();
	}
}

void AWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
}

void AWeapon::FireShot()
{
	AActor* MyOwner = GetOwner();
	check(MyOwner);

	APlayerController* PlayerController = Cast<APlayerController>(MyOwner->GetInstigatorController());
	check(PlayerController);

	FVector Location;
	FRotator Rotation;
	PlayerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + (Rotation.Vector() * 10000.0f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(MyOwner);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECC_Visibility, Params);

	DrawDebugLine(GetWorld(), Location, End, FColor::Red, false, 10.0f, 0, 1.0f);

	if (bHit && Hit.GetActor())
	{
		UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, PlayerController, this, nullptr);
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 10.0f, FColor::Yellow, false, 10.0f);
	}
}
