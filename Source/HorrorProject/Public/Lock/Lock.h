#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interaction/InteractInterface.h"
#include "Lock.generated.h"

UCLASS()
class HORRORPROJECT_API ALock : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractableFound_Implementation() override;

	virtual void InteractWithObject_Implementation() override;

public:
	void CheckEveryTurn();

private:
	UFUNCTION()
	void ExitLockView();

	UFUNCTION()
	void MouseKeyPressed();

	UFUNCTION()
	void MouseKeyReleased();

private:
	void CheckCode(bool& bWasSuccessful);

	void ExitInteraction();

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacterController> PC;

	UPROPERTY()
	TObjectPtr<class ALockDial> LockDial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> LockRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> LockMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> LockCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Box, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> LockBoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetInteractionComponent> WidgetInteraction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimationAsset> LockAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Dial, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class ALockDial>> LockDialArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Dial, meta = (AllowPrivateAccess = "true"))
	TArray<FName> SocketNameArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Dial, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class ALockDial>> LockDialClassArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Box, meta = (AllowPrivateAccess = "true"))
	FVector BoxPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Box, meta = (AllowPrivateAccess = "true"))
	FVector BoxExtent;

private:
	bool bIsUnlocked;

	int32 FirstNumber;
	int32 SecondNumber;
	int32 ThirdNumber;
	int32 FourthNumber;

	TArray<int32>LockCombinationArray;

	double ExitInteractionTimer;

	FTimerHandle ExitInteractionTimerHandle;
};
