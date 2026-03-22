
#include "Target.h"
#include "AimTrainer/Settings/AimTrainerUserSettings.h"
#include "Components/MeshComponent.h"

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

	if (UAimTrainerUserSettings* Settings = UAimTrainerUserSettings::GetAimTrainerUserSettings())
	{
		const FLinearColor SelectedColor = Settings->TargetColor;

		TInlineComponentArray<UMeshComponent*> MeshComponents(this);
		GetComponents(MeshComponents);

		for (UMeshComponent* Mesh : MeshComponents)
		{
			if (!Mesh)
			{
				continue;
			}

			const int32 MaterialCount = Mesh->GetNumMaterials();
			for (int32 i = 0; i < MaterialCount; i++)
			{
				if (UMaterialInstanceDynamic* DynamicMat = Mesh->CreateAndSetMaterialInstanceDynamic(i))
				{
					DynamicMat->SetVectorParameterValue(TEXT("TargetColor"), SelectedColor);
					DynamicMat->SetVectorParameterValue(TEXT("Color"), SelectedColor);
				}
			}
		}
	}
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

