#include "HideActors/Locker/Locker.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ALocker::ALocker() : bIsOpen(false), bIsReady(true), RotateValue(1.F), CurveFloatValue(0.F), TimelineValue(0.F), DoorRotation(FRotator(0.F))
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Door Mesh");
	DoorMesh->SetupAttachment(BaseMesh);
}

void ALocker::BeginPlay()
{
	Super::BeginPlay();

	InitializeDoor();

	OnFinishedMoving.AddDynamic(this, &ALocker::CloseDoor);
}

void ALocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorTimeline.TickTimeline(DeltaTime);
}

void ALocker::InteractWithObject_Implementation()
{
	if (bCanInteract)
	{
		bCanInteract = false;

		ToggleDoor();
	}
}

void ALocker::ControlDoor()
{
	TimelineValue = DoorTimeline.GetPlaybackPosition();

	CurveFloatValue = RotateValue * DoorCurve->GetFloatValue(TimelineValue);

	double Alpha{ UKismetMathLibrary::Lerp(0.0, -90.0, CurveFloatValue) };

	FQuat NewRotation = FQuat(FRotator(0.0, Alpha, 0.0));

	DoorMesh->SetRelativeRotation(NewRotation);
}

void ALocker::ToggleDoor()
{
	if (bIsReady)
	{
		bIsOpen = !bIsOpen;

		FVector PawnLocation = PlayerRef->GetActorLocation();
		FVector Direction = GetActorLocation() - PawnLocation;

		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

		DoorRotation = DoorMesh->GetRelativeRotation();

		if (bIsOpen)
		{
			if (Direction.X > 0.F)
				RotateValue = 1.F;

			else
				RotateValue = -1.F;

			bIsReady = false;

			DoorTimeline.PlayFromStart();
		}

		else
		{
			bIsReady = false;

			DoorTimeline.Reverse();
		}
	}
}

void ALocker::SetState()
{
	AHideActor::InteractWithObject_Implementation();

	bIsReady = true;
}

void ALocker::InitializeDoor()
{
	if (DoorCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("ControlDoor"));

		TimelineFinishedCallback.BindUFunction(this, FName("SetState"));

		DoorTimeline.AddInterpFloat(DoorCurve, TimelineCallback);
		DoorTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

void ALocker::CloseDoor()
{
	TimelineValue = DoorTimeline.GetPlaybackPosition();

	CurveFloatValue = RotateValue * DoorCurve->GetFloatValue(TimelineValue);

	double Alpha{ UKismetMathLibrary::Lerp(0.0, 0.0, CurveFloatValue) };

	FQuat NewRotation = FQuat(FRotator(0.0, Alpha, 0.0));

	DoorMesh->SetRelativeRotation(NewRotation);

	bCanInteract = true;
}

