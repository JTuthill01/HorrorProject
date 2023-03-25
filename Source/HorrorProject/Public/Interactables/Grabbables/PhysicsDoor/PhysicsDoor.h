#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsDoor.generated.h"

UCLASS()
class HORRORPROJECT_API APhysicsDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BaseRoot, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> BaseRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Door;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPhysicsConstraintComponent> PhysComp;
};
