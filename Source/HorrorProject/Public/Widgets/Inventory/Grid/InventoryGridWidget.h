#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryGridWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE TArray<TObjectPtr<class UInventorySlotWidget>> GetSlotsArray() const { return SlotsArray; }

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> InventoryGridPannel;

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacterController> PC;

	UPROPERTY()
	TObjectPtr<class UInventorySlotWidget> SlotWidget;

	UPROPERTY()
	TArray<TObjectPtr<class UInventorySlotWidget>> SlotsArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widgets, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InventorySlotSubclass;

private:
	int32 SlotsPerRow;
};
