#include "Interactables/Base/InteractableBase.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Base Root Component"));
	SetRootComponent(BaseRootComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");
	BaseMesh->SetupAttachment(BaseRootComponent);
	BaseMesh->SetCastShadow(false);
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableBase::InteractableFound_Implementation()
{
	
}

void AInteractableBase::InteractWithObject_Implementation()
{
}



