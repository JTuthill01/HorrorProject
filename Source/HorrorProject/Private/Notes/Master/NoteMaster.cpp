#include "Notes/Master/NoteMaster.h"
#include "Components/TextRenderComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ANoteMaster::ANoteMaster() : NoteText(FText())
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	NoteRootComponent = CreateDefaultSubobject<USceneComponent>(L"Note Root");
	SetRootComponent(NoteRootComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");
	BaseMesh->SetupAttachment(NoteRootComponent);
	BaseMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(L"Text Render");
	TextRender->SetupAttachment(BaseMesh);

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(L"Overlap Sphere");
	OverlapSphere->SetupAttachment(NoteRootComponent);
}

// Called when the game starts or when spawned
void ANoteMaster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANoteMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANoteMaster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	TextRender->SetText(NoteText);
}

