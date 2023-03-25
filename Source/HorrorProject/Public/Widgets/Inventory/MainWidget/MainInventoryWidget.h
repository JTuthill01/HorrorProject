#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemData/Str_ItemData.h"
#include "MainInventoryWidget.generated.h"

UCLASS()
class HORRORPROJECT_API UMainInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMainInventoryWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void CloseDropDownMenu();

public: 
	void OpenDropDownMenu(TObjectPtr<class UInventorySlotWidget> OpenSlot);

	void ShowItemInfo(FItemData ItemData);

	void HideItemInfo();

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UInventoryGridWidget> GridWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UInventoryDropDownWidget> InventoryDropDownWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BackgroundButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> ItemInfoVerticalBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> DescriptionText;
};
