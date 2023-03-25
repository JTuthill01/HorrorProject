#pragma once

#include "CoreMinimal.h"
#include "Inventory/Master/InventoryItemMaster.h"
#include "InventoryItemDoorKey.generated.h"

UCLASS()
class HORRORPROJECT_API AInventoryItemDoorKey : public AInventoryItemMaster
{
	GENERATED_BODY()
	
public:
	AInventoryItemDoorKey();

public:
	virtual void UseItem() override;
};
