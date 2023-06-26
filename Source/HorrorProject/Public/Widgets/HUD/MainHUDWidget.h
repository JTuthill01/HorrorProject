#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMainHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBarWidgets> ProgressBars;

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;
};
