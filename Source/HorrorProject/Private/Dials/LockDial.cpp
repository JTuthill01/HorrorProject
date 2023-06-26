#include "Dials/LockDial.h"
#include "Lock/Lock.h"
#include "Widgets/Arrow/ArrowWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WidgetComponent.h"

// Sets default values
ALockDial::ALockDial() : Index(0), DisplayNumber(0), DialRotation(0.0), CurveFloatValue(0.0), TimelineValue(0.0), Alpha(0.0), NegativeAlpha(0.0), DialTimer(1.0), bCanRotate(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LockDialRootComponent = CreateDefaultSubobject<USceneComponent>(L"Lock Dial Root");
	SetRootComponent(LockDialRootComponent);

	LockDialMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Lock Mesh");
	LockDialMesh->SetupAttachment(LockDialRootComponent);
	LockDialMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	UpArrowWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(L"Up Arrow Widget Component");
	DownArrowWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(L"Down Arrow Widget Component");

	static ConstructorHelpers::FClassFinder<UUserWidget> ArrowWidgetClassFinder(L"WidgetBlueprint'/Game/_Main/Blueprints/Widgets/Arrow/WBP_Arrow.WBP_Arrow_C'");

	UpArrowWidgetComponent->SetWidgetClass(ArrowWidgetClassFinder.Class);
	UpArrowWidgetComponent->AttachToComponent(LockDialRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	UpArrowWidgetComponent->SetVisibility(true);

	DownArrowWidgetComponent->SetWidgetClass(ArrowWidgetClassFinder.Class);
	DownArrowWidgetComponent->SetupAttachment(LockDialRootComponent);
	DownArrowWidgetComponent->SetVisibility(true);
}

// Called when the game starts or when spawned
void ALockDial::BeginPlay()
{
	Super::BeginPlay();

	WidgetSetup();

	DialTimeline.SetPropertySetObject(this);
	DialTimeline.SetDirectionPropertyName(FName("TimelineDirection"));
	
	SetRandomNumber();

	InitializeDial();
}

void ALockDial::InitializeDial()
{
	if (IsValid(DialCurve))
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("RotateDial"));
		TimelineFinishedCallback.BindUFunction(this, FName("SetDialState"));

		DialTimeline.AddInterpFloat(DialCurve, TimelineCallback);
		DialTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

// Called every frame
void ALockDial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DialTimeline.TickTimeline(DeltaTime);
}

void ALockDial::RotateDial()
{
	TimelineValue = DialTimeline.GetPlaybackPosition();

	CurveFloatValue = DialCurve->GetFloatValue(DialTimeline.GetPlaybackPosition());

	if (TimelineDirection == ETimelineDirection::Forward)
		Alpha = (UKismetMathLibrary::Lerp(36.0, 0.0, CurveFloatValue)) + DialRotation;

	else if (TimelineDirection == ETimelineDirection::Backward)
		Alpha = (UKismetMathLibrary::Lerp(-36.0, 0.0, CurveFloatValue)) + DialRotation;

	FQuat NewRotation = FQuat(FRotator(0.0, 0.0, Alpha));

	LockDialMesh->SetRelativeRotation(NewRotation);
}

void ALockDial::RotateDialBackwards()
{
	if (bCanRotate)
	{
		bCanRotate = false;

		DialTimeline.ReverseFromEnd();
	}
}

void ALockDial::RotateDialForwards()
{
	if (bCanRotate)
	{
		bCanRotate = false;

		DialTimeline.PlayFromStart();
	}
}

void ALockDial::SetRandomNumber()
{
	double LocalRotation{ UKismetMathLibrary::RandomIntegerInRange(0, 9) * 36.0 };

	FQuat NewRotation = FQuat(FRotator(0.0, 0.0, LocalRotation));

	LockDialMesh->SetRelativeRotation(NewRotation);

	DialRotation = LocalRotation;

	FindNumber();
}

void ALockDial::WidgetSetup()
{
	UpArrowWidget = Cast<UArrowWidget>(UpArrowWidgetComponent->GetUserWidgetObject());
	DownArrowWidget = Cast<UArrowWidget>(DownArrowWidgetComponent->GetUserWidgetObject());

	if (IsValid(UpArrowWidget))
		UpArrowWidget->Init(this, true);

	if (IsValid(DownArrowWidget))
		DownArrowWidget->Init(this, false);
}

void ALockDial::SetDialState()
{ 
	DialRotation = Alpha;

	if (DialRotation >= 360.0)
	{
		DialRotation = 0.0;

		FQuat NewRotation = FQuat(0.0);

		LockDialMesh->SetRelativeRotation(NewRotation);

		FindNumber();
	}

	else if (DialRotation > 0.0 && DialRotation < 360.0)
	{
		DialRotation = UKismetMathLibrary::MapRangeClamped(DialRotation, 0.0, -360.0, 360.0, 0.0);

		FQuat NewRotation = FQuat(FRotator(0.0, 0.0, DialRotation));

		LockDialMesh->SetRelativeRotation(NewRotation);

		FindNumber();
	}

	if (IsValid(LockRef))
		LockRef->CheckEveryTurn();

	bCanRotate = true;
}

void ALockDial::FindNumber() { DisplayNumber = UKismetMathLibrary::Abs_Int(static_cast<int32>(DialRotation / 36.0)); }
