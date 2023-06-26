#include "Components/Flashlight/FlashlightComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SpotLightComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UFlashlightComponent::UFlashlightComponent() : MaxBatteryLevel(100.0), CurrentBatteryLevel(MaxBatteryLevel), MinBatteryLevel(0.0), DepletionAmount(1.0), BatteryTimer(0.3)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Light = CreateDefaultSubobject<USpotLightComponent>(L"Light Comp");
}


// Called when the game starts
void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Light = PlayerRef->GetFlashlight();
}


// Called every frame
void UFlashlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFlashlightComponent::ToggleFlashLight()
{
	if (!IsValid(Light))
		return;

	if (Light->IsVisible())
	{
		Light->SetVisibility(false);

		GetWorld()->GetTimerManager().ClearTimer(BatteryTimerHandle);
	}

	else
	{
		if (CurrentBatteryLevel > MinBatteryLevel)
		{
			SetIntensity();

			Light->SetVisibility(true);

			GetWorld()->GetTimerManager().SetTimer(BatteryTimerHandle, this, &UFlashlightComponent::DepleteBatteryLife, BatteryTimer, true);
		}
	}
}

void UFlashlightComponent::DepleteBatteryLife()
{
	CurrentBatteryLevel -= DepletionAmount;

	CurrentBatteryLevel = FMath::Clamp(CurrentBatteryLevel, MinBatteryLevel, MaxBatteryLevel);

	SetIntensity();

	if (CurrentBatteryLevel <= MinBatteryLevel)
	{
		Light->SetVisibility(false);

		GetWorld()->GetTimerManager().ClearTimer(BatteryTimerHandle);
	}
}

void UFlashlightComponent::AddBatteryLife(double InBatteryLife)
{
	CurrentBatteryLevel = FMath::Clamp(CurrentBatteryLevel + InBatteryLife, MinBatteryLevel, MaxBatteryLevel);

	SetIntensity();
}

void UFlashlightComponent::SetIntensity()
{
	double LocalIntensity = UKismetMathLibrary::MapRangeClamped(CurrentBatteryLevel, MinBatteryLevel, MaxBatteryLevel, 0.0, 1.0);

	if (Light->bUseIESBrightness)
		Light->SetIESBrightnessScale(LocalIntensity);

	else
		Light->SetIntensity(LocalIntensity);
}

