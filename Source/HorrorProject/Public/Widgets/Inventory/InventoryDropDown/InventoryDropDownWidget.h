#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryDropDownWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UInventoryDropDownWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryDropDownWidget(const FObjectInitializer& ObjectInitializer);

	void UpdateMenu(TObjectPtr<class UInventorySlotWidget> InSlot);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnUseButtonRelease();

	UFUNCTION()
	void OnDropButtonRelease();

	UFUNCTION()
	void OnExamineButtonReleased();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> UseButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> ExamineButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> DropButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> UseSection;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> ExamineSection;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> DropSection;

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

private:
	int32 SlotIndex;
};
