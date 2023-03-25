#include "Widgets/Inventory/InventoryDropDown/InventoryDropDownWidget.h"
#include "Widgets/Inventory/Slot/InventorySlotWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Inventory/Master/InventoryItemMaster.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"

UInventoryDropDownWidget::UInventoryDropDownWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), SlotIndex(0)
{
}

void UInventoryDropDownWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	UseButton->IsFocusable = false;
	ExamineButton->IsFocusable = false;
	DropButton->IsFocusable = false;

	UseButton->OnReleased.AddDynamic(this, &UInventoryDropDownWidget::OnUseButtonRelease);
	DropButton->OnReleased.AddDynamic(this, &UInventoryDropDownWidget::OnDropButtonRelease);
	ExamineButton->OnReleased.AddDynamic(this, &UInventoryDropDownWidget::OnExamineButtonReleased);
}

void UInventoryDropDownWidget::OnUseButtonRelease()
{
	if (IsValid(PlayerRef))
		PlayerRef->GetInventoryComponent()->UseItem(SlotIndex);

	else
	{
		PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (IsValid(PlayerRef))
			PlayerRef->GetInventoryComponent()->UseItem(SlotIndex);

		else
			return;
	}
}

void UInventoryDropDownWidget::OnDropButtonRelease()
{
	if (IsValid(PlayerRef))
		PlayerRef->GetInventoryComponent()->DropItem(SlotIndex);
}

void UInventoryDropDownWidget::OnExamineButtonReleased()
{
	if (IsValid(PlayerRef))
		PlayerRef->GetInventoryComponent()->CreateExaminationWidget(SlotIndex);
}

void UInventoryDropDownWidget::UpdateMenu(TObjectPtr<UInventorySlotWidget> InSlot)
{
	SlotIndex = InSlot->GetIndex();

	int32 Amount = 0;

	TSubclassOf<AInventoryItemMaster> LocalItem = nullptr;

	PlayerRef->GetInventoryComponent()->GetItemAtIndex(SlotIndex, Amount, LocalItem);

	if (UKismetSystemLibrary::IsValidClass(LocalItem))
	{
		const bool& bLocalCanBeUsed = LocalItem.GetDefaultObject()->GetItemData().bCanBeUsed;

		if (bLocalCanBeUsed)
			UseSection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		else
			UseSection->SetVisibility(ESlateVisibility::Collapsed);
	}
}
