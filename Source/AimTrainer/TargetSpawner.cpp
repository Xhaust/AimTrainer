// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSpawner.h"
#include "Kismet/KismetMathLibrary.h"

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

	FVector RandomOffset = Origin + FMath::RandPointInBox(FBox::BuildAABB(Origin, SpawnAreaExtent));
	FTransform SpawnTransform(FRotator::ZeroRotator, RandomOffset);

	AActor* SpawnedTarget = GetWorld()->SpawnActor<AActor>(TargetClass, SpawnTransform);

	if (SpawnedTarget)
	{
		SpawnedTarget->OnDestroyed.AddDynamic(this, &ATargetSpawner::OnTargetDestroyed);
	}
}

void ATargetSpawner::OnTargetDestroyed(AActor* DestroyedActor)
{
	CurrentTargets = FMath::Max(0, CurrentTargets - 1);
}
