#include "Widgets/Inventory/Exam/ExaminationWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Inventory/Master/InventoryItemMaster.h"
#include "Inventory/Examination/InventoryExamination.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

UExaminationWidget::UExaminationWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UExaminationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UExaminationWidget::UpdateWidget(int32 InIndex)
{
	if (!IsValid(PlayerRef))
		PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	int32 LocalAmount = NULL;

	TSubclassOf<AInventoryItemMaster> LocalSubclass = nullptr;

	PlayerRef->GetInventoryComponent()->GetItemAtIndex(InIndex, LocalAmount, LocalSubclass);

	//GEngine->AddOnScreenDebugMessage(-1, 8.F, FColor::Yellow, LocalSubclass.GetDefaultObject()->GetItemData().ItemName.ToString());

	PlayerRef->GetInventoryComponent()->GetInventoryExaminationRef()->GetExaminationMesh()->SetStaticMesh(LocalSubclass.GetDefaultObject()->GetItemData().ExamMesh);

	const float& LocalX = PlayerRef->GetInventoryComponent()->GetInventoryExaminationRef()->GetExaminationMesh()->GetComponentLocation().X;
	const float& LocalY = PlayerRef->GetInventoryComponent()->GetInventoryExaminationRef()->GetExaminationMesh()->GetComponentLocation().Y;
	const float& LocalZ = PlayerRef->GetInventoryComponent()->GetInventoryExaminationRef()->GetExaminationMesh()->GetComponentLocation().Z;

	FVector NewLocation{ LocalSubclass.GetDefaultObject()->GetItemData().ExaminationMeshOffset + LocalX, LocalY,  LocalZ };

	PlayerRef->GetInventoryComponent()->GetInventoryExaminationRef()->GetExaminationMesh()->SetRelativeLocation(NewLocation);

	ItemNameText->SetText(FText::FromName(LocalSubclass.GetDefaultObject()->GetItemData().ItemName));

	ItemDescriptionText->SetText(LocalSubclass.GetDefaultObject()->GetItemData().ItemDescription);
}
