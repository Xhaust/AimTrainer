// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSpawner.h"
#include "AimTrainerGameMode.h"

// Sets default values
ATargetSpawner::ATargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		if (CurrentTargets < MaxTargets)
	{
		SpawnTarget();
                CurrentTargets++;
	}

}

void ATargetSpawner::SpawnTarget()
{
	if (!TargetClass) return;

	FVector Origin = GetActorLocation();

	FVector RandomOffset = FMath::RandPointInBox(FBox::BuildAABB(Origin, SpawnAreaExtent));
	FTransform SpawnTransform(FRotator::ZeroRotator, RandomOffset);

	ATarget* SpawnedTarget = GetWorld()->SpawnActor<ATarget>(TargetClass, SpawnTransform);
	AAimTrainerGameMode* GameMode = Cast<AAimTrainerGameMode>(GetWorld()->GetAuthGameMode());

	if (SpawnedTarget)
	{
		SpawnedTarget->OnTargetDestroyed.AddDynamic(this, &ATargetSpawner::OnTargetDestroyed);
		SpawnedTarget->OnTargetDestroyed.AddDynamic(GameMode, &AAimTrainerGameMode::HandleTargetDestroyed);
	}
}

void ATargetSpawner::OnTargetDestroyed(ATarget* DestroyedTarget)
{
	CurrentTargets = FMath::Max(0, CurrentTargets - 1);
}
