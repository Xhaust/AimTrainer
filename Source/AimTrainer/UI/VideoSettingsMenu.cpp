
#include "VideoSettingsMenu.h"

void UVideoSettingsMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ResolutionCombo->AddOption("1280x720");
	ResolutionCombo->AddOption("1920x1080");
	ResolutionCombo->AddOption("2560x1440");

	WindowModeCombo->AddOption("Fullscreen");
	WindowModeCombo->AddOption("Windowed");
	WindowModeCombo->AddOption("Borderless");

	QualityCombo->AddOption("Low");
	QualityCombo->AddOption("Medium");
	QualityCombo->AddOption("High");
	QualityCombo->AddOption("Epic");

	ApplyButton->OnClicked.AddDynamic(this, &ThisClass::OnApplyClicked);
}