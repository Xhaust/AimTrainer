#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "GameFramework/Actor.h"
#include "TargetSpawner.generated.h"

UCLASS()
class AIMTRAINER_API ATargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetSpawner();

	// Track spawned targets for reliable reset
	UPROPERTY()
	TArray<ATarget*> SpawnedTargets;

	// Reset spawner state and destroy any targets it spawned
	UFUNCTION()
	void ResetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> TargetClass;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 MaxTargets = 3;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector SpawnAreaExtent = FVector(500.0f, 500.0f, 500.0f);

	int32 CurrentTargets = 0;

	void SpawnTarget();

	UFUNCTION()
	void OnTargetDestroyed(ATarget* DestroyedTarget);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
