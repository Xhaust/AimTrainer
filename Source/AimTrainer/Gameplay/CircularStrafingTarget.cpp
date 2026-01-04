// Fill out your copyright notice in the Description page of Project Settings.


#include "CircularStrafingTarget.h"
#include "AimTrainerGameMode.h"
#include "Kismet/GameplayStatics.h"

ACircularStrafingTarget::ACircularStrafingTarget()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionProfileName(TEXT("BlockAll"));
	Mesh->SetGenerateOverlapEvents(true);
}

void ACircularStrafingTarget::BeginPlay()
{
	Super::BeginPlay();

	Center = GetActorLocation();

	if (Radius <= KINDA_SMALL_NUMBER)
	{
		Radius = 200.f;
	}

	AngleRad = FMath::RandRange(0.f, 2.f * PI);
	Direction = FMath::RandBool() ? 1.f : -1.f;

	FVector InitialLocation = Center + FVector(FMath::Cos(AngleRad) * Radius, FMath::Sin(AngleRad) * Radius, 0.f);
	SetActorLocation(InitialLocation, false, nullptr, ETeleportType::TeleportPhysics);

	OnTakeAnyDamage.AddDynamic(this, &ACircularStrafingTarget::OnTargetDamaged);

	GetWorldTimerManager().SetTimer(
		DirectionTimer,
		this,
		&ACircularStrafingTarget::ChangeDirection,
		DirectionChangeInterval,
		true
	);
}

void ACircularStrafingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float AngularSpeedRad = FMath::DegreesToRadians(AngularSpeedDeg);
	AngleRad += Direction * AngularSpeedRad * DeltaTime;

	FVector NewLocation = Center;
	NewLocation.X += FMath::Cos(AngleRad) * Radius;
	NewLocation.Y += FMath::Sin(AngleRad) * Radius;

	SetActorLocation(NewLocation, true);
}

void ACircularStrafingTarget::ChangeDirection()
{
	Direction = FMath::RandBool() ? 1.f : -1.f;
}

void ACircularStrafingTarget::OnTargetDamaged(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (AAimTrainerGameMode* GM =
		Cast<AAimTrainerGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GM->AddScore(1);
	}
}
