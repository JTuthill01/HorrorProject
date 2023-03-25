#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractPromptWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UInteractPromptWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInteractPromptWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> InteractPromptText;

private:
	FVector2D GetScreenSize();

	FVector2D ScreenSize;
};
