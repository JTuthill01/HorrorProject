#pragma once

#include "CoreMinimal.h"
#include "Interactables/Base/InteractableBase.h"
#include "LightSwitch.generated.h"

UCLASS()
class HORRORPROJECT_API ALightSwitch : public AInteractableBase
{
	GENERATED_BODY()
	
public:
	ALightSwitch();

public:
	virtual void InteractableFound_Implementation() override;

	virtual void InteractWithObject_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
	class ALight* Light;
};
