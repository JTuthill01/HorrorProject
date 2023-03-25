#include "Interactables/Grabbables/PhysicsDoor/PhysicsDoor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
APhysicsDoor::APhysicsDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base Root Component"));
	SetRootComponent(BaseRootComponent);

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(L"Door Frame");
	DoorFrame->SetupAttachment(BaseRootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(L"Door");
	Door->SetupAttachment(DoorFrame);
	Door->SetSimulatePhysics(true);

	PhysComp = CreateDefaultSubobject <UPhysicsConstraintComponent>(L"Physics Comp");
	PhysComp->SetupAttachment(BaseRootComponent);
}

// Called when the game starts or when spawned
void APhysicsDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APhysicsDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

