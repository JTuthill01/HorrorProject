#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORPROJECT_API UMovementComp : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE float GetCurrentStamina() const { return CurrentStamina; }

public:	
	// Sets default values for this component's properties
	UMovementComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartSprint();

	void StopSprint();

	void StartCrouch();

private:
	void Initialize();

	void SetPlayerMaxWalkSpeed(float InSpeed);

	void ControlSprint();

	void RegenerateStamina();

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina, meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina, meta = (AllowPrivateAccess = "true"))
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina, meta = (AllowPrivateAccess = "true"))
	float MinStamina;

private:
	float SprintTimer;
	float RegenerateStaminaTimer;

	float CrouchSpeed;
	float CrouchHalfHeight;

	FTimerHandle SprintTimerHandle;
	FTimerHandle RegenerateStaminaTimerHandle;
};
