#pragma once

#include "CoreMinimal.h"
#include "Inventory/Master/InventoryItemMaster.h"
#include "Battery.generated.h"

UCLASS()
class HORRORPROJECT_API ABattery : public AInventoryItemMaster
{
	GENERATED_BODY()
	
public:
	ABattery();

public:
	virtual void UseItem() override;
};
