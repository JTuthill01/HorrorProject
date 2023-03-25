#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction/InteractInterface.h"
#include "InteractableBase.generated.h"

UCLASS()
class HORRORPROJECT_API AInteractableBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InteractableFound_Implementation() override;

	virtual void InteractWithObject_Implementation() override;

protected:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BaseRoot)
	TObjectPtr<class USceneComponent> BaseRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> BaseMesh;
};
