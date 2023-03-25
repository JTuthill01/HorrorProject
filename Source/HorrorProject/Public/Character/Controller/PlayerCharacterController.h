#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Components/TimelineComponent.h"
#include "PlayerCharacterController.generated.h"

class UInputAction;

UCLASS()
class HORRORPROJECT_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerCharacterController();

	FORCEINLINE TObjectPtr<class UMainInventoryWidget> GetMainInventoryWidget() const { return MainInventoryWidget; }
	FORCEINLINE TObjectPtr<class UExaminationWidget> GetExamWidget() const { return ExamWidget; }

	FORCEINLINE int32 GetInventorySlotsIndex() const { return InventorySlotsIndex; }

public:
	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

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
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> InventoryAction;

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
	//void StartCrouch();
	//void StopCrouch();
	void OpenCloseInventory();

#pragma endregion

//#pragma region Timeline
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FloatCurve, meta = (AllowPrivateAccess = "true"))
//	TObjectPtr<class UCurveFloat> CrouchCurve;
//
//	FTimeline CrouchTimeline;
//
//	void SetupCrouchTimeline();
//
//#pragma endregion

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
};
