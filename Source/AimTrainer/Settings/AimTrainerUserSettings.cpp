
#include "AimTrainerUserSettings.h"

UAimTrainerUserSettings* UAimTrainerUserSettings::GetAimTrainerUserSettings()
{
	return Cast<UAimTrainerUserSettings>(GetGameUserSettings());
}
