#include "Components/Health/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() : MinHealth(0.0), MaxHealth(100.0), CurrentHealth(MaxHealth)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> ObjectType(L"MaterialParameterCollection'/Game/_Main/Blueprints/Misc/MPC_BloodScreen.MPC_BloodScreen'");

	if (ObjectType.Succeeded())
		Collection = ObjectType.Object;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateBloodScreen();
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::AddHealth(double InAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + InAmount, MinHealth, MaxHealth);
}

void UHealthComponent::RemoveHealth(double InAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - InAmount, MinHealth, MaxHealth);
}

void UHealthComponent::UpdateBloodScreen()
{
	double Value = UKismetMathLibrary::MapRangeClamped(CurrentHealth, MinHealth, MaxHealth, 0.5, 1.0);

	TObjectPtr<UMaterialParameterCollectionInstance> Instance = GetWorld()->GetParameterCollectionInstance(Collection);

	if (IsValid(Instance))
		Instance->SetScalarParameterValue("Amount", Value);
}
