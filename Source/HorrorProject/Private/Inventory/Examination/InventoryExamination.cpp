#include "Inventory/Examination/InventoryExamination.h"

// Sets default values
AInventoryExamination::AInventoryExamination()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Mesh");
	Mesh->SetCastShadow(false);

	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AInventoryExamination::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInventoryExamination::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

