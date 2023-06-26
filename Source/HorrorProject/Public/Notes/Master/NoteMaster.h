#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoteMaster.generated.h"

UCLASS()
class HORRORPROJECT_API ANoteMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoteMaster();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> NoteRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTextRenderComponent> TextRender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> OverlapSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	FText NoteText;
};
