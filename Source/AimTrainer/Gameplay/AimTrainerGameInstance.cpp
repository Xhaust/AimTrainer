
#include "AimTrainerGameInstance.h"

void UAimTrainerGameInstance::Init()
{
	Super::Init();

	AimTrainerUserSettings = UAimTrainerUserSettings::GetAimTrainerUserSettings();
	if (AimTrainerUserSettings)
	{
		AimTrainerUserSettings->LoadSettings();
	}

	const FString CrosshairDir = FPaths::ProjectSavedDir() / TEXT("Crosshairs");

	IFileManager::Get().MakeDirectory(*CrosshairDir, true);

	FString SourcePath = FPaths::ProjectContentDir() / TEXT("Crosshairs/Dot.png");

	FString DestPath = CrosshairDir / TEXT("Dot.png");

	if (!FPaths::FileExists(DestPath))
	{
		IFileManager::Get().Copy(*DestPath, *SourcePath);
	}
}

FString UAimTrainerGameInstance::GetCurrentMapName() const
{
	if (!GetWorld()) return TEXT("Unknown");

	FString MapName = GetWorld()->GetMapName();

	// Remove PIE prefix (UEDPIE_0_)
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	return MapName;
}