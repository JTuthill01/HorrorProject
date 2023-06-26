#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "PlayerCharacterController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseLockInteraction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLockWidgetInteraction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLockWidgetInteractionReleased);


class UInputAction;

UCLASS()
class HORRORPROJECT_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	FORCEINLINE TObjectPtr<class UMainInventoryWidget> GetMainInventoryWidget() const { return MainInventoryWidget; }
	FORCEINLINE TObjectPtr<class UExaminationWidget> GetExamWidget() const { return ExamWidget; }

	FORCEINLINE int32 GetInventorySlotsIndex() const { return InventorySlotsIndex; }
	FORCEINLINE bool GetCanOpenInventory() const { return bCanOpenInventory; }

	FORCEINLINE void SetCanOpenInventory(bool Val) { bCanOpenInventory = Val; }
	FORCEINLINE void SetCanCloseLockInteract(bool NewVal) { bCanCloseLockInteract = NewVal; }
	FORCEINLINE void SetCanInteractWithWidget(bool InValue) { bCanInteractWithWidget = InValue; }
	
public:
	APlayerCharacterController();

public:
	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;

public:
	void CaputureMouse();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnCloseLockInteraction OnCloseLockInteraction;

	UPROPERTY(BlueprintAssignable)
	FOnLockWidgetInteraction OnLockWidgetInteraction;

	UPROPERTY(BlueprintAssignable)
	FOnLockWidgetInteractionReleased OnLockWidgetInteractionReleased;

protected:
#pragma region INPUT

	//Input Actions//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> WeaponFireAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> WeaponReloadAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> FlashlightToggleAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LockInteractCloseAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LockWidgetInteractAction;

	//Input Functions//
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void Jump();
	void StopJump();
	void WeaponFire();
	void StopFiringWeapon();
	void WeaponReload();
	void ToggleFlashlight();
	void StartSprint();
	void StopSprint();
	void CloseLockInteract();
	void ResetLockInteract();
	void StartLockWidgetInteraction();
	void StopLockWidgetInteraction();
	void OpenCloseInventory();

private:
	void SetupInventoryWidget();

	void SetupExamWidget();

private:
	UPROPERTY()
	TObjectPtr<class APlayerCharacter> PlayerRef;

	UPROPERTY()
	TObjectPtr<class UMainInventoryWidget> MainInventoryWidget;

	UPROPERTY()
	TObjectPtr<class UExaminationWidget> ExamWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widgets, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> InventoryWidgetSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widgets, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ExamWidgetSubclass;

private:
	int32 InventorySlotsIndex;

	bool bIsVisible;
	bool bCanOpenInventory;
	bool bCanCloseLockInteract;
	bool bCanInteractWithWidget;
};
