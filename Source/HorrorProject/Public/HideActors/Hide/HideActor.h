#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction/InteractInterface.h"
#include "HideActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedMoving);

UCLASS()
class HORRORPROJECT_API AHideActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHideActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractableFound_Implementation() override;

	virtual void InteractWithObject_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void MoveCharacter();

	void FinishedMoving();

protected:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY()
	TObjectPtr<class APlayerCharacterController> PC;

	UPROPERTY()
	FOnFinishedMoving OnFinishedMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<class USceneComponent> DefaultComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Arrows)
	TObjectPtr<class UArrowComponent> PlayerPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Arrows)
	TObjectPtr<class UArrowComponent> ExitPosition;

protected:
	bool bCanInteract;

private:
	double MoveCharacterTimer;

	FTimerHandle MoveCharacterTimerHandle;
};
