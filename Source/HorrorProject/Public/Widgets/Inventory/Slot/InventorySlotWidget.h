#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemData/Str_ItemData.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE int32 GetIndex() const { return Index; }

	FORCEINLINE void SetIndex(int32 InIndex) { Index = InIndex; }

public: 
	void UpdateSlots();

	void Init(TObjectPtr<class UMainInventoryWidget> MainInventoryRef);

protected:
	void NativeConstruct() override;

	UFUNCTION()
	void OnReleased();

	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnUnHovered();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> SlotButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> SlotImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SlotText;

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY()
	TObjectPtr<class UTexture2D> InactiveTexture;

	UPROPERTY()
	TObjectPtr<class UMainInventoryWidget> MainInventoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	int32 Index;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	int32 Amount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;
};
