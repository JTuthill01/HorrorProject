#include "Character/Player/PlayerCharacter.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Interfaces/Interaction/InteractInterface.h"
#include "Widgets/HUD/MainHUDWidget.h"
#include "Components/Movement/MovementComp.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Components/Flashlight/FlashlightComponent.h"
#include "Components/Health/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : InteractableTraceTimer(0.25F), bIsHiding(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);
	Arms->SetCastShadow(false);

	MovementComp = CreateDefaultSubobject<UMovementComp>(L"Movement Comp");

	FlashLightSpringArm = CreateDefaultSubobject<USpringArmComponent>(L"FlashLight SpringArm");
	FlashLightSpringArm->SetupAttachment(Camera);
	FlashLightSpringArm->TargetArmLength = 10.F;
	FlashLightSpringArm->SocketOffset = FVector(0.F, 0.F, 30.F);
	FlashLightSpringArm->bEnableCameraRotationLag = true;

	FlashLight = CreateDefaultSubobject<USpotLightComponent>(L"Flashlight");
	FlashLight->SetVisibility(false);
	FlashLight->SetupAttachment(FlashLightSpringArm);

	FlashLightComp = CreateDefaultSubobject<UFlashlightComponent>(L"FlashLightComp");

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(L"Inventory Component");

	HealthComp = CreateDefaultSubobject<UHealthComponent>(L"Health Component");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(InteractableTraceTimerHandle, this, &APlayerCharacter::ScanForInteractables, InteractableTraceTimer, true);

	HUDWidget = CreateWidget<UMainHUDWidget>(GetWorld(), HUDWidgetClass);

	if (IsValid(HUDWidget))
		HUDWidget->AddToViewport();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(InteractableTraceTimerHandle);

	InteractableTraceTimer = 0.25F;

	UKismetSystemLibrary::QuitGame(GetWorld(), 0, EQuitPreference::Quit, false);
}

void APlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController.
	if (TObjectPtr<APlayerCharacterController> PC = Cast<APlayerCharacterController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values out prioritize lower values.
			Subsystem->AddMappingContext(PlayerBaseMappingContext, BaseMappingPriority);
		}
	}
}

void APlayerCharacter::InteractWithObject()
{
	FHitResult HitResult;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetComponentRotation().Vector() * 400.F);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(this);

	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	const bool bCanInteract = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

	if (bCanInteract)
	{
		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
				IInteractInterface::Execute_InteractWithObject(HitResult.GetActor());
		}
	}
}

void APlayerCharacter::ScanForInteractables()
{
	FHitResult HitResult;

	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetComponentRotation().Vector() * 400.F);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjects;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(this);

	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TraceObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	const bool bIsInteractable = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjects, true, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

	if (bIsInteractable)
	{
		if (HitResult.GetActor())
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
				IInteractInterface::Execute_InteractableFound(HitResult.GetActor());
		}
	}

	else
		OnClearViewport.Broadcast();
}

APlayerCharacter* APlayerCharacter::GetPlayerRef_Implementation() { return this; }

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) { Super::SetupPlayerInputComponent(PlayerInputComponent); }