// Fill out your copyright notice in the Description page of Project Settings.


#include "AimTrainerGameMode.h"
#include "AimTrainerGameInstance.h"
#include "AimTrainerPlayerController.h"
#include "EngineUtils.h"
#include "TargetSpawner.h"
#include "UserScores.h"
#include "../UI/HUDWidget.h"
#include "Kismet/GameplayStatics.h"

void AAimTrainerGameMode::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
	if (HUDWidget)
		HUDWidget->AddToViewport();

	if (CurrentMode == EGameModeType::TimedSession)
	{
		StartSession();
	}
}

void AAimTrainerGameMode::StartSession()
{
	if (CurrentMode == EGameModeType::TimedSession)
	{
		TimeRemaining = SessionDuration;
		PlayerScore = 0.f;

		if (HUDWidget)
		{
			HUDWidget->UpdateTimer(TimeRemaining);
			HUDWidget->UpdateScore(PlayerScore);
		}

		GetWorldTimerManager().SetTimer(
			SessionTimerHandle,
			this,
			&AAimTrainerGameMode::TickSession,
			1.0f,
			true
		);
	}
	AAimTrainerPlayerController* PC = Cast<AAimTrainerPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC)
	{
		PC->CloseAllMenus();
	}
}

void AAimTrainerGameMode::EndSession()
{
	GetWorldTimerManager().ClearTimer(SessionTimerHandle);

	if (CurrentMode == EGameModeType::TimedSession && TimeRemaining <= 0.f)
	{
		if (UAimTrainerGameInstance* GI = GetGameInstance<UAimTrainerGameInstance>())
		{
			const FString MapName = GI->GetCurrentMapName();
			SaveScore(MapName, PlayerScore);
		}

		AAimTrainerPlayerController* PC = Cast<AAimTrainerPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC)
		{
			PC->OpenScoreboard();
		}

		OnSessionEnded.Broadcast();
	}
	PlayerScore = 0.0f;
}

void AAimTrainerGameMode::TickSession()
{
	TimeRemaining -= 1.0f;
	
	if (HUDWidget)
		HUDWidget->UpdateTimer(TimeRemaining);
	
	if (TimeRemaining <= 0.f)
	{
		EndSession();
	}
	OnTimerUpdated.Broadcast(TimeRemaining);
}

void AAimTrainerGameMode::HandleTargetDestroyed(ATarget* DestroyedTarget)
{
	AddScore(1.0f);
}

void AAimTrainerGameMode::AddScore(int32 Points)
{
	PlayerScore += Points;
	if (HUDWidget)
	{
		HUDWidget->UpdateScore(PlayerScore);
	}
}

void AAimTrainerGameMode::ToggleGameMode()
{
	if (CurrentMode == EGameModeType::TimedSession)
	{
		CurrentMode = EGameModeType::Playground;
		EndSession();
		if (HUDWidget)
		{
			HUDWidget->UpdateGameModeText(TEXT("Playground"));
		}
	}
	else
	{
		CurrentMode = EGameModeType::TimedSession;
		StartSession();
		if (HUDWidget)
		{
			HUDWidget->UpdateGameModeText(TEXT("Timed Session"));
		}
	}
}

void AAimTrainerGameMode::SaveScore(const FString& ScenarioName, float Score)
{
	UUserScores* Save =
		Cast<UUserScores>(UGameplayStatics::LoadGameFromSlot(TEXT("UserScores"), 0));

	if (!Save)
	{
		Save = Cast<UUserScores>(UGameplayStatics::CreateSaveGameObject(UUserScores::StaticClass()));
	}

	FScenarioScores* Scenario = Save->ScenarioScores.FindByPredicate([&](const FScenarioScores& S)
		{
			return S.ScenarioName == ScenarioName;
		}
	);

	if (!Scenario)
	{
		Save->ScenarioScores.Add(FScenarioScores(ScenarioName));
		Scenario = &Save->ScenarioScores.Last();
	}

	// format: Achieved on MM/DD/YYYY HH:MM:SS
	const FString NowString = FDateTime::Now().ToString(TEXT("Achieved on %m/%d/%Y %H:%M:%S"));
	Scenario->History.Add(FScenarioScoreEntry(Score, NowString));
	Scenario->HighScore = FMath::Max(Scenario->HighScore, Score);

	UGameplayStatics::SaveGameToSlot(Save, TEXT("UserScores"), 0);
}

void AAimTrainerGameMode::RestartSession()
{
    // End any running session safely (assumes EndSession exists)
    EndSession();

    // Destroy all spawned targets so we start clean
    for (TActorIterator<ATarget> It(GetWorld()); It; ++It)
    {
        if (IsValid(*It))
        {
            (*It)->Destroy();
        }
    }

    // Reset all spawners so their internal counters are cleared
    for (TActorIterator<ATargetSpawner> It(GetWorld()); It; ++It)
    {
        if (IsValid(*It))
        {
            (*It)->ResetSpawner();
        }
    }

    // Respawn the local player pawn
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        APawn* Pawn = PC->GetPawn();
        if (Pawn)
        {
            Pawn->Destroy();
        }
        RestartPlayer(PC);
    }

    // Start a fresh session
    StartSession();
}