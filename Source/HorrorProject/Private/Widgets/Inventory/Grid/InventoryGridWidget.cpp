#include "Widgets/Inventory/Grid/InventoryGridWidget.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Widgets/Inventory/Slot/InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UInventoryGridWidget::UInventoryGridWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), SlotsPerRow(4)
{
}

void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryGridWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (IsValid(PC))
	{
		for (int32 i = 0; i < PC->GetInventorySlotsIndex(); ++i)
		{
			SlotWidget = CreateWidget<UInventorySlotWidget>(GetWorld(), InventorySlotSubclass);

			if (IsValid(SlotWidget))
			{
				SlotWidget->SetIndex(i);

				SlotsArray.Emplace(SlotWidget);

				int32 InRow = UKismetMathLibrary::FTrunc(static_cast<float>(i) / static_cast<float>(SlotsPerRow));

				double InColumn = 0;

				UKismetMathLibrary::FMod(static_cast<float>(i), static_cast<float>(SlotsPerRow), InColumn);

				int32 Column = UKismetMathLibrary::FTrunc(InColumn);

				InventoryGridPannel->AddChildToUniformGrid(SlotWidget, InRow, Column);
			}

			else
				return;
		}
	}
}
