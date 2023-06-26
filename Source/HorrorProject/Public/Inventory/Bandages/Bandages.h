#pragma once

#include "CoreMinimal.h"
#include "Inventory/Master/InventoryItemMaster.h"
#include "Bandages.generated.h"

UCLASS()
class HORRORPROJECT_API ABandages : public AInventoryItemMaster
{
	GENERATED_BODY()
	
public:
	ABandages();

public:
	virtual void UseItem() override;

protected:
	virtual void BeginPlay() override;

private:
	double AmountOfHealthToAdd;
};
