#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Player/PlayerRefInterface.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClearViewport);

UCLASS()
class HORRORPROJECT_API APlayerCharacter : public ACharacter, public IPlayerRefInterface
{
	GENERATED_BODY()

public:

	FORCEINLINE TObjectPtr<class UCameraComponent> GetPlayerCamera() const { return Camera; }
	FORCEINLINE TObjectPtr<class USpotLightComponent> GetFlashlight() const { return FlashLight; }
	FORCEINLINE TObjectPtr<class UMovementComp> GetMovementComp() const { return MovementComp; }
	FORCEINLINE TObjectPtr<class UInventoryComponent> GetInventoryComponent() const { return InventoryComponent; }
	FORCEINLINE TObjectPtr<class UFlashlightComponent> GetFlashLightComp() const { return FlashLightComp; }
	FORCEINLINE TObjectPtr<class UHealthComponent> GetHealthComponent() const { return HealthComp; }

	FORCEINLINE bool GetIsHiding() const { return bIsHiding; }

public:
	FORCEINLINE void SetIsHiding(bool Hiding) { bIsHiding = Hiding; }

public:
	// Sets default values for this character's properties
	APlayerCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called on Player Death 
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PawnClientRestart() override;

	APlayerCharacter* GetPlayerRef_Implementation() override;

public:
	void InteractWithObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ScanForInteractables();

public:
	UPROPERTY(BlueprintAssignable)
	FOnClearViewport OnClearViewport;

protected:
	//Mapping Contexts//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InputMappings)
	TObjectPtr<class UInputMappingContext> PlayerBaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InputMappings)
	int32 BaseMappingPriority = 0;

private:
	UPROPERTY()
	TObjectPtr<UAnimInstance> PlayerAnimInstance;

	UPROPERTY()
	TObjectPtr<class UMainHUDWidget> HUDWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HUD, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UMainHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SK_Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Arms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Light, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpotLightComponent> FlashLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Light, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> FlashLightSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMovementComp> MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFlashlightComponent> FlashLightComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HealthComp;

private:
	float InteractableTraceTimer;

	FTimerHandle InteractableTraceTimerHandle;

	bool bIsHiding;
};

