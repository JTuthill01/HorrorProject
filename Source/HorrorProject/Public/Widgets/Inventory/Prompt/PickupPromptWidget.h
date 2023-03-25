#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupPromptWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UPickupPromptWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPickupPromptWidget(const FObjectInitializer& ObjectInitializer);
};
