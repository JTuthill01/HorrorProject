#include "Widgets/Inventory/MainWidget/MainInventoryWidget.h"
#include "Widgets/Inventory/InventoryDropDown/InventoryDropDownWidget.h"
#include "Widgets/Inventory/Grid/InventoryGridWidget.h"
#include "Widgets/Inventory/Slot/InventorySlotWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/VerticalBox.h"
#include "Components/UniformGridSlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

UMainInventoryWidget::UMainInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMainInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	BackgroundButton->SetFocus();
}

void UMainInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const TArray<TObjectPtr<UInventorySlotWidget>>& LocalSlotsArray = GridWidget->GetSlotsArray();

	for (auto& Slots : LocalSlotsArray)
		Slots->Init(this);

	InventoryDropDownWidget->SetVisibility(ESlateVisibility::Collapsed);

	BackgroundButton->SetVisibility(ESlateVisibility::Collapsed);

	ItemInfoVerticalBox->SetVisibility(ESlateVisibility::Hidden);

	BackgroundButton->OnPressed.AddDynamic(this, &UMainInventoryWidget::CloseDropDownMenu);
}

void UMainInventoryWidget::OpenDropDownMenu(TObjectPtr<class UInventorySlotWidget> OpenSlot)
{
	const FMargin& LocalPadding = GridWidget->InventoryGridPannel->SlotPadding;

	float LeftRightPadding = LocalPadding.Left + LocalPadding.Right;
	float TopBottomPadding = LocalPadding.Top + LocalPadding.Bottom;

	auto&& GridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(OpenSlot);

	FVector2D LocalSize = OpenSlot->GetDesiredSize();

	int32 LocalRow = GridSlot->Row * (LeftRightPadding + UKismetMathLibrary::FTrunc(LocalSize.X)) + 10;

	int32 LocalColumn = GridSlot->Column * (TopBottomPadding + UKismetMathLibrary::FTrunc(LocalSize.Y)) - 10;

	FVector2D RenderTranslation = FVector2D(LocalRow, LocalColumn);

	InventoryDropDownWidget->SetRenderTranslation(RenderTranslation);

	InventoryDropDownWidget->UpdateMenu(OpenSlot);

	InventoryDropDownWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	BackgroundButton->SetVisibility(ESlateVisibility::Visible);
}

void UMainInventoryWidget::ShowItemInfo(FItemData ItemData)
{
	ItemNameText->SetText(FText::FromName(ItemData.ItemName));

	DescriptionText->SetText(ItemData.ItemDescription);

	ItemInfoVerticalBox->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UMainInventoryWidget::HideItemInfo()
{
	ItemInfoVerticalBox->SetVisibility(ESlateVisibility::Hidden);
}

void UMainInventoryWidget::CloseDropDownMenu()
{
	InventoryDropDownWidget->SetVisibility(ESlateVisibility::Collapsed);

	BackgroundButton->SetVisibility(ESlateVisibility::Collapsed);
}

