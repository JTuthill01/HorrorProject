#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlashlightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORPROJECT_API UFlashlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlashlightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void ToggleFlashLight();

	void DepleteBatteryLife();

	void AddBatteryLife(double InBatteryLife);

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpotLightComponent> Light;

public:
	double MaxBatteryLevel;
	double CurrentBatteryLevel;
	double MinBatteryLevel;
	double DepletionAmount;

	FTimerHandle BatteryTimerHandle;

	float BatteryTimer;
};
