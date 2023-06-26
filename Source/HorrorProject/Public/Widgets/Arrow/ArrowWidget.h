#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArrowWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UArrowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UArrowWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

public:
	void Init(class ALockDial* InDial, bool InRotation);

private:
	UFUNCTION()
	void AddRotation();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ArrowButton;

private:
	UPROPERTY()
	TObjectPtr<class ALockDial> LockDialRef;

private:
	bool bAddRotation;
};
