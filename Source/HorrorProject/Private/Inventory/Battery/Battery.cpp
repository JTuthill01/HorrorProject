#include "Inventory/Battery/Battery.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/Flashlight/FlashlightComponent.h"

ABattery::ABattery()
{
	ItemFilePath = L"BlueprintGeneratedClass'/Game/_Main/Blueprints/Pickups/BP_BatteryPickup.BP_BatteryPickup_C'";

	ItemData.ExamMesh = LoadObject<UStaticMesh>(this, L"StaticMesh'/Game/_Main/Props/SM_Battery.SM_Battery'");
	ItemData.ItemName = FName("Battery");
	ItemData.ItemDescription = FText::FromString("Juice up your flashlight");
	ItemData.MaxStackAmount = 8;
	ItemData.ItemIcon = LoadObject<UTexture2D>(this, L"Texture2D'/Game/_Main/Textures/BatteryIcon.BatteryIcon'");

	AInventoryItemMaster::LoadItem(ItemFilePath, ActorBpClass, ItemData.PickupActor);
}

void ABattery::UseItem()
{
	Super::UseItem();

	if (!IsValid(PlayerRef))
		return;

	double BatteryAmount = 100.0;

	if (PlayerRef->GetFlashLightComp()->CurrentBatteryLevel < PlayerRef->GetFlashLightComp()->MaxBatteryLevel)
	{
		PlayerRef->GetFlashLightComp()->AddBatteryLife(BatteryAmount);

		bUseItemSucessfully = true;
	}

	else
		bUseItemSucessfully = false;
}
