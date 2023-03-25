#include "Lights/Flickering/FlickeringLight.h"
#include "Components/PointLightComponent.h"

// Sets default values
AFlickeringLight::AFlickeringLight() : Intensity(5'000.F), IntensityTimer(0.F), MinTime(0.1F), MaxTime(0.3F), bIsA(true), bIsB(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Light = CreateDefaultSubobject<UPointLightComponent>(L"Light");
	Light->SetIntensity(Intensity);
	SetRootComponent(Light);
}

// Called when the game starts or when spawned
void AFlickeringLight::BeginPlay()
{
	Super::BeginPlay();
	
	IntensityTimer = FMath::RandRange(MinTime, MaxTime);

	GetWorldTimerManager().SetTimer(IntensityTimerHandle, this, &AFlickeringLight::ChangeIntensity, IntensityTimer, true);
}

// Called every frame
void AFlickeringLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlickeringLight::ChangeIntensity()
{
	float MinFlickerIntensity = 3'000.F;

	if (bIsA)
	{
		bIsB = true;
		bIsA = false;

		Light->SetIntensity(MinFlickerIntensity);
	}

	else if (bIsB)
	{
		bIsB = false;
		bIsA = true;

		Light->SetIntensity(Intensity);
	}
}

