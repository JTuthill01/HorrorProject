#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/InventoryItems/Str_InventoryItems.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	FORCEINLINE TObjectPtr<class AInventoryExamination> GetInventoryExaminationRef() const { return InventoryExaminationRef; }

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool AddItems(TSubclassOf<class AInventoryItemMaster> InItemSubclass, int32 InAmount, int32& OutRemainder);

	bool RemoveItem(int32 InIndex);

	void CheckForEmptySlot(int32& OutIndex, bool& IsSuccessful);

	void CheckForFreeSlot(TSubclassOf<class AInventoryItemMaster> InItemSubclass, bool& IsSuccessful, int32& OutIndex);

	void GetItemAtIndex(int32 InIndex, int32& OutAmount, TSubclassOf<class AInventoryItemMaster>& OutItem);

	void UpdateInventorySlot(int32 InIndex);

	void UseItem(int32 InIndex);

	void DropItem(int32 InIndex);

	void CreateExaminationWidget(int32 InIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void ComponentSetup();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Struct)
	TArray<FInventoryItems> InventoryItemsArray;

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY()
	TObjectPtr<class APlayerCharacterController> PC;

	UPROPERTY()
	TObjectPtr<class AInventoryExamination> InventoryExaminationRef;

	UPROPERTY()
	TObjectPtr<class UMainInventoryWidget> InventoryWidgetRef;

	UPROPERTY()
	TObjectPtr<class UExaminationWidget> ExaminationWidgetRef;
};
