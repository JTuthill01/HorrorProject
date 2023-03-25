#include "Pickups/Base/PickupBase.h"
#include "Character/Player/PlayerCharacter.h"
#include "Interfaces/Player/PlayerRefInterface.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Widgets/Interact/InteractPromptWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APickupBase::APickupBase() : Amount(0), bIsVisible(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Pickup Root"));
	SetRootComponent(PickupRoot);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");
	BaseMesh->SetupAttachment(PickupRoot);
	BaseMesh->SetCastShadow(false);
	BaseMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	PickupWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Pickup Widget Component"));

	static ConstructorHelpers::FClassFinder<UUserWidget> PickupWidgetClassFinder(L"WidgetBlueprint'/Game/_Main/Blueprints/Widgets/Inventory/PickupPrompt/WBP_PickupPrompt.WBP_PickupPrompt_C'");

	PickupWidgetComponent->SetWidgetClass(PickupWidgetClassFinder.Class);
	PickupWidgetComponent->AttachToComponent(PickupRoot, FAttachmentTransformRules::KeepRelativeTransform);
	PickupWidgetComponent->SetVisibility(false);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(PlayerRef))
		PlayerRef->OnClearViewport.AddDynamic(this, &APickupBase::OnClearViewport);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsVisible)
	{
		FVector LocalLocation{ PickupWidgetComponent->GetComponentLocation() };

		FRotator LocalRotation{ UKismetMathLibrary::FindLookAtRotation(LocalLocation, PlayerRef->GetPlayerCamera()->GetComponentLocation()) };

		PickupWidgetComponent->SetWorldRotation(LocalRotation);
	}
}

void APickupBase::InteractableFound_Implementation()
{
	PickupWidgetComponent->SetVisibility(true);

	PromptText = FText::FromString("Press E To Pickup");

	if (!IsValid(InteractWidget))
	{
		InteractWidget = CreateWidget<UInteractPromptWidget>(GetWorld(), InteractWidgetSubclass);

		if (IsValid(InteractWidget))
		{
			InteractWidget->AddToViewport();

			InteractWidget->InteractPromptText->SetText(PromptText);

			bIsVisible = true;
		}
	}

	else if (IsValid(InteractWidget) && !InteractWidget->IsInViewport())
	{
		InteractWidget->AddToViewport();

		bIsVisible = true;
	}

	bIsVisible = true;
}

void APickupBase::InteractWithObject_Implementation()
{
	if (!IsValid(PlayerRef))
		return;

	int32 Remainder = 0;

	const bool bIsSuccessful = PlayerRef->GetInventoryComponent()->AddItems(ItemSubclass, Amount, Remainder);

	if (bIsSuccessful)
	{
		if (InteractWidget->IsInViewport())
		{
			InteractWidget->RemoveFromViewport();

			bIsVisible = false;
		}

		if (Remainder > NULL)
			Amount = Remainder;

		else
			Destroy();
	}
}

void APickupBase::OnClearViewport()
{
	if (bIsVisible)
	{
		PickupWidgetComponent->SetVisibility(false);

		InteractWidget->RemoveFromViewport();

		bIsVisible = false;
	}
}

