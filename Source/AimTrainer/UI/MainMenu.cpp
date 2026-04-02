
#include "MainMenu.h"

#include "AimTrainer/Gameplay/AimTrainerGameMode.h"
#include "AimTrainer/Gameplay/AimTrainerPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartEndGameButton)
	{
		UpdateStartEndButtonText();
		StartEndGameButton->OnClicked.AddDynamic(this, &UMainMenu::OnStartGameClicked);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UMainMenu::OnRestartClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &UMainMenu::OnSettingsMenuClicked);
	}

	if (VideoSettingsMenuButton)
	{
		VideoSettingsMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OnVideoSettingsMenuClicked);
	}
	
	if (MapSelectorButton)
	{
		MapSelectorButton->OnClicked.AddDynamic(this, &UMainMenu::OnMapSelectorClicked);
	}

	if (CrosshairSelectorButton)
	{
		CrosshairSelectorButton->OnClicked.AddDynamic(this, &UMainMenu::OnCrosshairSelectorClicked);
	}

	if (ScoreboardButton)
	{
		ScoreboardButton->OnClicked.AddDynamic(this, &UMainMenu::OnShowScoreboardClicked);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UMainMenu::OnExitGameClicked);
	}
}

void UMainMenu::OnStartGameClicked()
{
	AAimTrainerGameMode* GameMode = Cast<AAimTrainerGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->ToggleGameMode();
		UpdateStartEndButtonText();
	}
}

void UMainMenu::UpdateStartEndButtonText()
{
	if (AAimTrainerGameMode* GameMode = Cast<AAimTrainerGameMode>(GetWorld()->GetAuthGameMode()))
	{
		if (StartEndGameText)
		{
			StartEndGameText->SetText(
				GameMode->CurrentMode == EGameModeType::TimedSession ?
				FText::FromString("End Game") :
				FText::FromString("Start Game")
			);
		}
	}
}

void UMainMenu::OnRestartClicked()
{
	if (AAimTrainerGameMode* GameMode = Cast<AAimTrainerGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->RestartSession();
	}
}

void UMainMenu::OnSettingsMenuClicked()
{
	if (AAimTrainerPlayerController* PC =
		Cast<AAimTrainerPlayerController>(GetOwningPlayer()))
	{
		PC->OpenSettingsMenu();
	}
}

void UMainMenu::OnVideoSettingsMenuClicked()
{
	if (AAimTrainerPlayerController* PC =
		Cast<AAimTrainerPlayerController>(GetOwningPlayer()))
	{
		PC->OpenVideoSettingsMenu();
	}
}

void UMainMenu::OnMapSelectorClicked()
{
	if (AAimTrainerPlayerController* PC =
		Cast<AAimTrainerPlayerController>(GetOwningPlayer()))
	{
		PC->OpenMapSelector();
	}
}

void UMainMenu::OnCrosshairSelectorClicked()
{
	if (AAimTrainerPlayerController* PC =
		Cast<AAimTrainerPlayerController>(GetOwningPlayer()))
	{
		PC->OpenCrosshairSelector();
	}
}

void UMainMenu::OnShowScoreboardClicked()
{
	if (AAimTrainerPlayerController* PC =
		Cast<AAimTrainerPlayerController>(GetOwningPlayer()))
	{
		PC->OpenScoreboard();
	}
}

void UMainMenu::OnExitGameClicked()
{
	if (AAimTrainerPlayerController* PC =
		Cast<AAimTrainerPlayerController>(GetOwningPlayer()))
	{
		UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
	}
}