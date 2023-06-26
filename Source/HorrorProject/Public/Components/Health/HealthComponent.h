#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE double GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE double GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE double GetMinHealth() const { return MinHealth; }

public:	
	// Sets default values for this component's properties
	UHealthComponent();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void AddHealth(double InAmount);

	void RemoveHealth(double InAmount);

	void UpdateBloodScreen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UMaterialParameterCollection* Collection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	double MinHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	double MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	double CurrentHealth;
};

