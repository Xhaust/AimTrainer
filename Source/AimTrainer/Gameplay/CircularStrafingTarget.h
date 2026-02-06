#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CircularStrafingTarget.generated.h"

UCLASS()
class AIMTRAINER_API ACircularStrafingTarget : public AActor
{
	GENERATED_BODY()
	
public:
	ACircularStrafingTarget();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Movement
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Radius = 300.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AngularSpeedDeg = 90.f; // degrees per second

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DirectionChangeInterval = 2.0f;

	FVector Center;
	float AngleRad;
	float Direction;

	FTimerHandle DirectionTimer;

	void ChangeDirection();

	UFUNCTION()
	void OnTargetDamaged(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser
	);
};
