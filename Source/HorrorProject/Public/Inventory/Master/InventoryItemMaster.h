#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/ItemData/Str_ItemData.h"
#include "InventoryItemMaster.generated.h"

UCLASS()
class HORRORPROJECT_API AInventoryItemMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItemMaster();

public:
	FORCEINLINE FItemData GetItemData() const { return ItemData; }
	FORCEINLINE bool GetUseItemSucessfully() const { return bUseItemSucessfully; }

public:
	virtual void Tick(float DeltaTime) override;

	virtual void UseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void LoadItem(FString InFilePath, TSoftClassPtr<AActor> InActorBpClass, TObjectPtr<UClass>& OutClass);

protected:
	UPROPERTY()
	TSoftClassPtr<AActor> ActorBpClass;

	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Items)
	FItemData ItemData;

protected:
	FString ItemFilePath;

	bool bUseItemSucessfully;
};
