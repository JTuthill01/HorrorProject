#include "Character/Controller/PlayerCharacterController.h"
#include "Character/Player/PlayerCharacter.h"
#include "Widgets/Inventory/MainWidget/MainInventoryWidget.h"
#include "Widgets/Inventory/Exam/ExaminationWidget.h"
#include "Components/Movement/MovementComp.h"
#include "Components/Flashlight/FlashlightComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"

APlayerCharacterController::APlayerCharacterController() : InventorySlotsIndex(8), bIsVisible(false)
{}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(GetCharacter());

	SetupInventoryWidget();

	SetupExamWidget();

	//SetupCrouchTimeline();
}

void APlayerCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//CrouchTimeline.TickTimeline(DeltaTime);
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (TObjectPtr<UEnhancedInputComponent> PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacterController::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopJump);
		}

		if (WeaponFireAction)
		{
			PlayerEnhancedInputComponent->BindAction(WeaponFireAction, ETriggerEvent::Started, this, &APlayerCharacterController::WeaponFire);
			PlayerEnhancedInputComponent->BindAction(WeaponFireAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopFiringWeapon);
		}

		if (WeaponReloadAction)
			PlayerEnhancedInputComponent->BindAction(WeaponReloadAction, ETriggerEvent::Started, this, &APlayerCharacterController::WeaponReload);

		if (MovementAction)
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);

		if (LookAction)
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);

		if (InteractAction)
			PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacterController::Interact);

		if (FlashlightToggleAction)
			PlayerEnhancedInputComponent->BindAction(FlashlightToggleAction, ETriggerEvent::Started, this, &APlayerCharacterController::ToggleFlashlight);

		if (SprintAction)
		{
			PlayerEnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacterController::StartSprint);
			PlayerEnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopSprint);
		}

		/*if (CrouchAction)
		{
			PlayerEnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &APlayerCharacterController::StartCrouch);
		}*/

		if (InventoryAction)
			PlayerEnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &APlayerCharacterController::OpenCloseInventory);
	}
}

void APlayerCharacterController::Move(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0.F)
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), Value[1]);
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Value[0]);
	}
}

void APlayerCharacterController::Look(const FInputActionValue& Value)
{
	AddPitchInput(Value[1] * -1);
	AddYawInput(Value[0]);
}

void APlayerCharacterController::Interact()
{
	if (IsValid(PlayerRef))
		PlayerRef->InteractWithObject();
}

void APlayerCharacterController::Jump()
{
	GetCharacter()->Jump();
}

void APlayerCharacterController::StopJump()
{
	GetCharacter()->StopJumping();
}

void APlayerCharacterController::WeaponFire()
{
	//TODO: Logic here
}

void APlayerCharacterController::StopFiringWeapon()
{
	//TODO: Logic here
}

void APlayerCharacterController::WeaponReload()
{
	//TODO: Logic here
}

void APlayerCharacterController::ToggleFlashlight()
{
	if (!IsValid(PlayerRef))
		return;

	PlayerRef->GetFlashLightComp()->ToggleFlashLight();
}

void APlayerCharacterController::StartSprint()
{
	if (IsValid(PlayerRef->GetMovementComp()))
		PlayerRef->GetMovementComp()->StartSprint();
}

void APlayerCharacterController::StopSprint()
{
	if (IsValid(PlayerRef->GetMovementComp()))
		PlayerRef->GetMovementComp()->StopSprint();
}

//void APlayerCharacterController::StartCrouch()
//{
//
//}
//
//void APlayerCharacterController::StopCrouch()
//{
//}

void APlayerCharacterController::OpenCloseInventory()
{
	if (IsValid(MainInventoryWidget) && !bIsVisible)
	{
		bIsVisible = true;

		bShowMouseCursor = true;

		SetIgnoreMoveInput(true);

		SetIgnoreLookInput(true);

		MainInventoryWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		FInputModeGameAndUI Mode;

		Mode.SetHideCursorDuringCapture(false);

		Mode.SetWidgetToFocus(MainInventoryWidget->TakeWidget());

		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		SetInputMode(Mode);
	}

	else if (IsValid(MainInventoryWidget) && bIsVisible)
	{
		MainInventoryWidget->SetVisibility(ESlateVisibility::Hidden);

		bIsVisible = false;

		SetIgnoreMoveInput(false);

		SetIgnoreLookInput(false);

		bShowMouseCursor = false;

		FInputModeGameOnly InputMode;

		SetInputMode(InputMode);

		InputMode.SetConsumeCaptureMouseDown(true);
	}
}

void APlayerCharacterController::SetupInventoryWidget()
{
	if (!IsValid(MainInventoryWidget))
	{
		MainInventoryWidget = CreateWidget<UMainInventoryWidget>(GetWorld(), InventoryWidgetSubclass);

		if (IsValid(MainInventoryWidget))
		{
			MainInventoryWidget->AddToViewport();

			MainInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void APlayerCharacterController::SetupExamWidget()
{
	ExamWidget = CreateWidget<UExaminationWidget>(GetWorld(), ExamWidgetSubclass);
}

//void APlayerCharacterController::SetupCrouchTimeline()
//{
//	if (CrouchCurve)
//	{
//		FOnTimelineFloat TimelineCallback;
//		FOnTimelineEventStatic TimelineFinishedCallback;
//
//		TimelineCallback.BindUFunction(this, FName("StartCrouch"));
//		TimelineFinishedCallback.BindUFunction(this, FName("StopCrouch"));
//	}
//}

