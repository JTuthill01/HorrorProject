#pragma once

#include "CoreMinimal.h"
#include "HideActors/Hide/HideActor.h"
#include "Components/TimelineComponent.h"
#include "Locker.generated.h"

UCLASS()
class HORRORPROJECT_API ALocker : public AHideActor
{
	GENERATED_BODY()
	
public:
	ALocker();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithObject_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ControlDoor();

	UFUNCTION()
	void ToggleDoor();

	UFUNCTION()
	void SetState();

	UFUNCTION()
	void InitializeDoor();

	UFUNCTION()
	void CloseDoor();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FloatCurve, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCurveFloat> DoorCurve;

private:
	FTimeline DoorTimeline;

	bool bIsOpen;
	bool bIsReady;

	float RotateValue;
	float CurveFloatValue;
	float TimelineValue;

	FRotator DoorRotation;
};
