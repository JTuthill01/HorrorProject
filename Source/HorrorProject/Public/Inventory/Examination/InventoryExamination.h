#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryExamination.generated.h"

UCLASS()
class HORRORPROJECT_API AInventoryExamination : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryExamination();

	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetExaminationMesh() const { return Mesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
};
