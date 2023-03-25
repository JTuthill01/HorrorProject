#include "Widgets/Inventory/Slot/InventorySlotWidget.h"
#include "Interfaces/Player/PlayerRefInterface.h"
#include "Character/Player/PlayerCharacter.h"
#include "Structs/ItemData/Str_ItemData.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Inventory/Master/InventoryItemMaster.h"
#include "Widgets/Inventory/MainWidget/MainInventoryWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UInventorySlotWidget::UInventorySlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), Index(0), Amount(0)
{
	InactiveTexture = LoadObject<UTexture2D>(this, L"Texture2D'/Game/_Main/Textures/EmptyIcon.EmptyIcon'");
}

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlotText->SetVisibility(ESlateVisibility::Hidden);

	SlotButton->OnReleased.AddDynamic(this, &UInventorySlotWidget::OnReleased);

	SlotButton->OnHovered.AddDynamic(this, &UInventorySlotWidget::OnHovered);

	SlotButton->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::OnUnHovered);
}

void UInventorySlotWidget::OnReleased()
{
	MainInventoryWidget->OpenDropDownMenu(this);
}

void UInventorySlotWidget::OnHovered()
{
	int32 LocalAmount = NULL;

	TSubclassOf<AInventoryItemMaster> LocalSubclass = nullptr;

	PlayerRef->GetInventoryComponent()->GetItemAtIndex(Index, LocalAmount, LocalSubclass);

	const FItemData& DataRef = LocalSubclass.GetDefaultObject()->GetItemData();

	MainInventoryWidget->ShowItemInfo(DataRef);
}

void UInventorySlotWidget::OnUnHovered()
{
	MainInventoryWidget->HideItemInfo();
}

void UInventorySlotWidget::UpdateSlots()
{
	if (!IsValid(PlayerRef))
		return;

	int32 LocalAmount = 0;

	TSubclassOf<AInventoryItemMaster> LocalSubclass = nullptr;

	PlayerRef->GetInventoryComponent()->GetItemAtIndex(Index, LocalAmount, LocalSubclass);

	if (UKismetSystemLibrary::IsValidClass(LocalSubclass))
	{
		SlotButton->SetIsEnabled(true);

		SlotImage->SetBrushFromTexture(LocalSubclass.GetDefaultObject()->GetItemData().ItemIcon, true);

		SlotText->SetText(FText::AsNumber(LocalAmount));

		if (LocalAmount >= 1)
			SlotText->SetVisibility(ESlateVisibility::Visible);

		else
		{
			SlotText->SetVisibility(ESlateVisibility::Hidden);

			SlotImage->SetBrushFromTexture(InactiveTexture);

			SlotButton->SetIsEnabled(false);
		}
	}
}

void UInventorySlotWidget::Init(TObjectPtr<UMainInventoryWidget> MainInventoryRef)
{ 
	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	MainInventoryWidget = MainInventoryRef;

	SlotButton->SetIsEnabled(false);

	SlotImage->SetBrushFromTexture(InactiveTexture);

	SlotText->SetVisibility(ESlateVisibility::Hidden);
}
