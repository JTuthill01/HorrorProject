#include "Lock/Lock.h"
#include "Dials/LockDial.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALock::ALock() : BoxPosition(FVector(0.0)), BoxExtent(FVector(32.0)), bIsUnlocked(false), FirstNumber(9), SecondNumber(5), ThirdNumber(1), FourthNumber(6), ExitInteractionTimer(1.0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LockRootComponent = CreateDefaultSubobject<USceneComponent>(L"Lock Root");
	SetRootComponent(LockRootComponent);

	LockMesh = CreateDefaultSubobject<USkeletalMeshComponent>(L"Lock Mesh");
	LockMesh->SetupAttachment(LockRootComponent);

	LockCamera = CreateDefaultSubobject<UCameraComponent>(L"Lock Camera");
	LockCamera->SetupAttachment(LockRootComponent);
	LockCamera->SetFieldOfView(45.F);

	LockBoxCollider = CreateDefaultSubobject<UBoxComponent>(L"Lock Box Collider");
	LockBoxCollider->SetupAttachment(LockRootComponent);
	LockBoxCollider->SetBoxExtent(BoxExtent);
	LockBoxCollider->SetRelativeLocation(BoxPosition);
	LockBoxCollider->SetGenerateOverlapEvents(true);
	LockBoxCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(L"Widget Interaction");
	WidgetInteraction->InteractionSource = EWidgetInteractionSource::Mouse;
}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (IsValid(PC))
	{
		PC->OnCloseLockInteraction.AddDynamic(this, &ALock::ExitLockView);

		PC->OnLockWidgetInteraction.AddDynamic(this, &ALock::MouseKeyPressed);

		PC->OnLockWidgetInteractionReleased.AddDynamic(this, &ALock::MouseKeyReleased);
	}

	LockCombinationArray.Emplace(FirstNumber);
	LockCombinationArray.Emplace(SecondNumber);
	LockCombinationArray.Emplace(ThirdNumber);
	LockCombinationArray.Emplace(FourthNumber);

	FVector Location{ LockMesh->GetComponentLocation() };
	FRotator Rotation{ LockMesh->GetComponentRotation() };
	FVector Scale{ 1.0 };

	FTransform LocalTransform = UKismetMathLibrary::MakeTransform(Location, Rotation, Scale);

	for (int32 i = 0; i < LockDialClassArray.Num(); ++i)
	{
		if (LockDialClassArray.IsValidIndex(i))
		{
			LockDial = GetWorld()->SpawnActorDeferred<ALockDial>(LockDialClassArray[i], LocalTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			LockDial->SetIndex(i);

			LockDial->SetLockRef(this);

			UGameplayStatics::FinishSpawningActor(LockDial, LocalTransform);

			LockDialArray.Emplace(LockDial);
		}

		if (SocketNameArray.IsValidIndex(i))
			if(IsValid(LockDial))
				LockDial->AttachToComponent(LockMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketNameArray[i]);
	}
}

// Called every frame
void ALock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALock::InteractableFound_Implementation()
{
}

void ALock::InteractWithObject_Implementation()
{
	if (IsValid(PC))
	{
		PC->SetViewTargetWithBlend(LockCamera->GetOwner(), 1.F);

		PC->SetCanCloseLockInteract(true);

		PC->SetCanInteractWithWidget(true);

		TObjectPtr<APlayerCharacter> LocalPlayer = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if (IsValid(LocalPlayer))
		{
			LocalPlayer->GetCharacterMovement()->DisableMovement();

			PC->SetIgnoreLookInput(true);

			PC->SetCanOpenInventory(false);

			GetWorldTimerManager().SetTimer(ExitInteractionTimerHandle, this, &ALock::ExitInteraction, ExitInteractionTimer, false);
		}
	}
}

void ALock::CheckCode(bool& bWasSuccessful)
{
	for (int32 i = 0; i < LockDialArray.Num(); ++i)
	{
		if (IsValid(LockDialArray[i]))
		{
			if (LockDialArray.IsValidIndex(i) && LockCombinationArray.IsValidIndex(i))
			{
				if (LockDialArray[i]->GetDisplayNumber() == LockCombinationArray[i])
					bWasSuccessful = true;

				else
				{
					bWasSuccessful = false;

					break;
				}
			}
		}
	}
}

void ALock::CheckEveryTurn()
{
	bool bIsSuccessful = false;

	CheckCode(bIsSuccessful);

	if (bIsSuccessful && IsValid(LockAnim))
		LockMesh->PlayAnimation(LockAnim, false);
}

void ALock::ExitInteraction()
{
	GetWorldTimerManager().ClearTimer(ExitInteractionTimerHandle);

	ExitInteractionTimer = 1.0;

	EnableInput(PC);

	PC->bShowMouseCursor = true;
}

void ALock::ExitLockView()
{
	TObjectPtr<APlayerCharacter> LocalPlayer = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (IsValid(LocalPlayer))
	{
		PC->SetViewTargetWithBlend(LocalPlayer, 1.F);

		PC->SetCanCloseLockInteract(false);

		PC->SetCanInteractWithWidget(false);

		DisableInput(PC);

		PC->ResetIgnoreLookInput();

		PC->SetCanOpenInventory(true);

		PC->bShowMouseCursor = false;

		LocalPlayer->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void ALock::MouseKeyPressed() { WidgetInteraction->PressPointerKey(FKey("LeftMouseButton")); }

void ALock::MouseKeyReleased() { WidgetInteraction->ReleasePointerKey(FKey("LeftMouseButton")); }
