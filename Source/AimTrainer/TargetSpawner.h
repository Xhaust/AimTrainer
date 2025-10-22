// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSpawner.generated.h"

UCLASS()
class AIMTRAINER_API ATargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> TargetClass;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 MaxTargets = 3;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector SpawnAreaExtent = FVector(500.0f, 500.0f, 500.0f);

	int32 CurrentTargets = 0;

	void SpawnTarget();

	UFUNCTION()
	void OnTargetDestroyed(AActor* DestroyedActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
