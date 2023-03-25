#include "Inventory/DoorKey/InventoryItemDoorKey.h"

AInventoryItemDoorKey::AInventoryItemDoorKey()
{
	ItemFilePath = L"BlueprintGeneratedClass'/Game/_Main/Blueprints/Pickups/BP_DoorKey_Pickup.BP_DoorKey_Pickup_C'";

	ItemData.ExamMesh = LoadObject<UStaticMesh>(this, L"StaticMesh'/Game/_Main/Props/SM_GoldKey.SM_GoldKey'");
	ItemData.ItemName = FName("Door Key");
	ItemData.ItemDescription = FText::FromString("Unlocks a door, duh");
	ItemData.MaxStackAmount = 1;
	ItemData.ItemIcon = LoadObject<UTexture2D>(this, L"Texture2D'/Game/_Main/Textures/Key.Key'");
	ItemData.bCanBeUsed = true;

	AInventoryItemMaster::LoadItem(ItemFilePath, ActorBpClass, ItemData.PickupActor);
}

void AInventoryItemDoorKey::UseItem()
{
	Super::UseItem();
}
