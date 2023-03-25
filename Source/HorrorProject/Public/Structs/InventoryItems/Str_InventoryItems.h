#pragma once
#include "Str_InventoryItems.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItems
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AInventoryItemMaster> ItemSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Amount = 0;
};