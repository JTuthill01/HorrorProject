#include "Components/Movement/MovementComp.h"
#include "Character/Player/PlayerCharacter.h"
#include "Interfaces/Player/PlayerRefInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMovementComp::UMovementComp() : SprintSpeed(800.F), WalkSpeed(400.F), MaxStamina(100.F), CurrentStamina(MaxStamina), MinStamina(0.F), SprintTimer(0.1F), RegenerateStaminaTimer(0.1F), CrouchSpeed(200.F),
	CrouchHalfHeight(44.F)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMovementComp::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

// Called every frame
void UMovementComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMovementComp::Initialize()
{
	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SetPlayerMaxWalkSpeed(WalkSpeed);
}

void UMovementComp::SetPlayerMaxWalkSpeed(float InSpeed)
{
	if (IsValid(PlayerRef))
		PlayerRef->GetCharacterMovement()->MaxWalkSpeed = InSpeed;
}

void UMovementComp::ControlSprint()
{
	CurrentStamina = FMath::Clamp(CurrentStamina - 1, MinStamina, MaxStamina);

	GEngine->AddOnScreenDebugMessage(-1, 6.F, FColor::White, L"Current Stamina is: " + FString::SanitizeFloat(CurrentStamina));

	if (PlayerRef->GetVelocity().Size() > 10.F)
	{
		if (CurrentStamina <= MinStamina)
			StopSprint();
	}

	else
		StopSprint();
}

void UMovementComp::RegenerateStamina()
{
	CurrentStamina = FMath::Clamp(CurrentStamina + 1, MinStamina, MaxStamina);

	GEngine->AddOnScreenDebugMessage(-1, 6.F, FColor::White, L"Regen Stamina is: " + FString::SanitizeFloat(CurrentStamina));

	if (CurrentStamina >= MaxStamina)
		GetWorld()->GetTimerManager().ClearTimer(RegenerateStaminaTimerHandle);
}

void UMovementComp::StopSprint()
{
	GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);

	SetPlayerMaxWalkSpeed(WalkSpeed);

	if (!GetWorld()->GetTimerManager().IsTimerActive(SprintTimerHandle))
		GetWorld()->GetTimerManager().SetTimer(RegenerateStaminaTimerHandle, this, &UMovementComp::RegenerateStamina, RegenerateStaminaTimer, true);
}

void UMovementComp::StartCrouch()
{
	GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);

	SetPlayerMaxWalkSpeed(CrouchSpeed);
}

void UMovementComp::StartSprint()
{
	if (CurrentStamina > MinStamina && PlayerRef->GetVelocity().Size() > 10.F)
	{
		SetPlayerMaxWalkSpeed(SprintSpeed);

		GetWorld()->GetTimerManager().SetTimer(SprintTimerHandle, this, &UMovementComp::ControlSprint, SprintTimer, true);

		GetWorld()->GetTimerManager().ClearTimer(RegenerateStaminaTimerHandle);
	}
}
