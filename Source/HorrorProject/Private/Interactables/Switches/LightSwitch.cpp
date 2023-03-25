#include "Interactables/Switches/LightSwitch.h"
#include "Engine/Light.h"
#include "Components/LightComponent.h"

ALightSwitch::ALightSwitch()
{
}

void ALightSwitch::InteractableFound_Implementation()
{
	Super::InteractableFound_Implementation();
}

void ALightSwitch::InteractWithObject_Implementation()
{
	Super::InteractWithObject_Implementation();

	if (IsValid(Light))
	{
		if (Light->GetLightComponent()->IsVisible())
			Light->GetLightComponent()->SetVisibility(false);

		else
			Light->GetLightComponent()->SetVisibility(true);
	}

	else
		return;
}
