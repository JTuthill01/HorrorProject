#include "Inventory/Master/InventoryItemMaster.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInventoryItemMaster::AInventoryItemMaster() : ActorBpClass(nullptr), ItemData(FItemData()), ItemFilePath(""), bUseItemSucessfully(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AInventoryItemMaster::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	GEngine->AddOnScreenDebugMessage(-1, 8.F, FColor::Purple, __FUNCTION__);
}

// Called every frame
void AInventoryItemMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInventoryItemMaster::LoadItem(FString InFilePath, TSoftClassPtr<AActor> InActorBpClass, TObjectPtr<UClass>& OutClass)
{
	InActorBpClass = TSoftClassPtr<AActor>(FSoftObjectPath(InFilePath));

	OutClass = InActorBpClass.LoadSynchronous();
}

void AInventoryItemMaster::UseItem() {}
