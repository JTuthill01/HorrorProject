#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBarWidgets.generated.h"

class APlayerCharacter;

UCLASS()
class HORRORPROJECT_API UProgressBarWidgets : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UProgressBarWidgets(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	double GetHealthPrecent();

	UFUNCTION()
	double GetStaminaPrecent();

	UFUNCTION()
	double GetBatteryPrecent();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> StaminaBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> BatteryBar;

private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerRef;

	UPROPERTY()
	TWeakObjectPtr<class APlayerCharacter> Player;
};
