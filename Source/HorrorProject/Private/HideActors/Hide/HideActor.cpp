#include "HideActors/Hide/HideActor.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AHideActor::AHideActor() : bCanInteract(true), MoveCharacterTimer(0.0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultComponent = CreateDefaultSubobject<USceneComponent>(L"Default Component");
	SetRootComponent(DefaultComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");

	PlayerPosition = CreateDefaultSubobject<UArrowComponent>(L"Player Position");
	ExitPosition = CreateDefaultSubobject<UArrowComponent>(L"Exit Position");

	BaseMesh->SetupAttachment(DefaultComponent);

	PlayerPosition->SetupAttachment(DefaultComponent);
	ExitPosition->SetupAttachment(DefaultComponent);
}

// Called when the game starts or when spawned
void AHideActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void AHideActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHideActor::MoveCharacter()
{
	if (!IsValid(PlayerRef))
		return;

	if (!PlayerRef->GetIsHiding())
	{
		FVector NewLocation = UKismetMathLibrary::VInterpTo_Constant(PlayerRef->GetActorLocation(), PlayerPosition->GetComponentLocation(), GetWorld()->GetDeltaSeconds(), 1'000.F);

		FRotator Rotation = PlayerRef->GetActorRotation();

		FVector Scale{ 1.F };

		FTransform LocalTransform = UKismetMathLibrary::MakeTransform(NewLocation, Rotation, Scale);

		PlayerRef->SetActorTransform(LocalTransform);
	}

	else if (PlayerRef->GetIsHiding())
	{
		FVector NewLocation = UKismetMathLibrary::VInterpTo_Constant(PlayerRef->GetActorLocation(), ExitPosition->GetComponentLocation(), GetWorld()->GetDeltaSeconds(), 1'000.F);

		FRotator Rotation = PlayerRef->GetActorRotation();

		FVector Scale{ 1.F };

		FTransform LocalTransform = UKismetMathLibrary::MakeTransform(NewLocation, Rotation, Scale);

		PlayerRef->SetActorTransform(LocalTransform);
	}

	if (PlayerRef->GetActorLocation() == PlayerPosition->GetComponentLocation() || PlayerRef->GetActorLocation() == ExitPosition->GetComponentLocation())
	{
		GetWorldTimerManager().ClearTimer(MoveCharacterTimerHandle);

		MoveCharacterTimer = 0.0;

		FinishedMoving();
	}
}

void AHideActor::FinishedMoving()
{
	if (!IsValid(PlayerRef) || !IsValid(PC))
		return;

	OnFinishedMoving.Broadcast();

	if (PlayerRef->GetIsHiding())
	{
		PlayerRef->SetIsHiding(false);

		PlayerRef->SetActorEnableCollision(true);

		PlayerRef->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		PC->SetCanOpenInventory(true);
	}

	else if (!PlayerRef->GetIsHiding())
		PlayerRef->SetIsHiding(true);
}

void AHideActor::InteractableFound_Implementation()
{
}

void AHideActor::InteractWithObject_Implementation()
{
	if (!IsValid(PlayerRef) || !IsValid(PC))
		return;

	if (!PlayerRef->GetIsHiding())
	{
		PlayerRef->SetActorEnableCollision(false);

		PlayerRef->GetCharacterMovement()->DisableMovement();

		PC->SetCanOpenInventory(false);

		MoveCharacterTimer = GetWorld()->GetDeltaSeconds();

		GetWorldTimerManager().SetTimer(MoveCharacterTimerHandle, this, &AHideActor::MoveCharacter, MoveCharacterTimer, true);
	}

	else
	{
		MoveCharacterTimer = GetWorld()->GetDeltaSeconds();

		GetWorldTimerManager().SetTimer(MoveCharacterTimerHandle, this, &AHideActor::MoveCharacter, MoveCharacterTimer, true);
	}
}

