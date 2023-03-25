#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExaminationWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UExaminationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UExaminationWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateWidget(int32 InIndex);

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemDescriptionText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> DragDetectionImage;

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;
};
