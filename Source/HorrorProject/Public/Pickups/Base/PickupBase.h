#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction/InteractInterface.h"
#include "PickupBase.generated.h"

UCLASS()
class HORRORPROJECT_API APickupBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

public:
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetBaseMesh() { return BaseMesh; }

	FORCEINLINE void SetAmount(int32 InAmount) { Amount = InAmount; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InteractableFound_Implementation() override;

	virtual void InteractWithObject_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnClearViewport();

protected:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY()
	TObjectPtr<class UInteractPromptWidget> InteractWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widget)
	TSubclassOf<UUserWidget> InteractWidgetSubclass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget)
	TObjectPtr<class UWidgetComponent> PickupWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PickupRoot)
	TObjectPtr<class USceneComponent> PickupRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables)
	TSubclassOf<class AInventoryItemMaster> ItemSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables)
	int32 Amount;

private:
	bool bIsVisible;

	FText PromptText;
};
