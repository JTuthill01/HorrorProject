#include "Inventory/Bandages/Bandages.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/Health/HealthComponent.h"

ABandages::ABandages() : AmountOfHealthToAdd(25.0)
{
	ItemFilePath = L"Blueprint'/Game/_Main/Blueprints/Pickups/BP_Bandages_Pickup.BP_Bandages_Pickup_C'";

	//ItemData.ExamMesh = LoadObject<UStaticMesh>(this, L"StaticMesh'/Game/_Main/Props/SM_Battery.SM_Battery'");
	ItemData.ExamMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, L"StaticMesh'/Game/_Main/Props/SM_Bandage.SM_Bandage'"));

	ItemData.ItemName = FName("Bandages");
	ItemData.ItemDescription = FText::FromString("Wrap it up");
	ItemData.MaxStackAmount = 4;
	ItemData.ItemIcon = LoadObject<UTexture2D>(UTexture2D::StaticClass(), L"Texture2D'/Game/_Main/Textures/HealthIcon.HealthIcon'");

	AInventoryItemMaster::LoadItem(ItemFilePath, ActorBpClass, ItemData.PickupActor);
}

void ABandages::BeginPlay()
{
	Super::BeginPlay();

	/*GEngine->AddOnScreenDebugMessage(-1, 8.F, FColor::Purple, __FUNCTION__);

	

	if (IsValid(ItemData.ExamMesh))
		GEngine->AddOnScreenDebugMessage(-1, 8.F, FColor::Green, L"Mesh" + ItemData.ExamMesh->GetName());

	else if (!IsValid(ItemData.ExamMesh))
		GEngine->AddOnScreenDebugMessage(-1, 8.F, FColor::Green, L"No mesh");*/
}

void ABandages::UseItem()
{
	Super::UseItem();

	if (IsValid(PlayerRef))
	{
		if (IsValid(PlayerRef->GetHealthComponent()))
		{
			if (PlayerRef->GetHealthComponent()->GetCurrentHealth() < PlayerRef->GetHealthComponent()->GetMaxHealth())
			{
				PlayerRef->GetHealthComponent()->AddHealth(AmountOfHealthToAdd);

				bUseItemSucessfully = true;
			}

			else
				bUseItemSucessfully = false;
		}
	}
			
}

