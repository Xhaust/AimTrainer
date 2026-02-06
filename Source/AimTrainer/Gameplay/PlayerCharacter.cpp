
#include "PlayerCharacter.h"
#include "Weapon.h"
#include "GameFramework/PlayerController.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (DefaultWeaponClass)
	{
		// Spawn the weapon
		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
		if (CurrentWeapon)
		{
			// Set the owner (important for line trace and ApplyDamage)
			CurrentWeapon->SetOwner(this);
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

void APlayerCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void APlayerCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}