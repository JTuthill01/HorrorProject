#include "Components/Inventory/InventoryComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Inventory/Master/InventoryItemMaster.h"
#include "Inventory/Examination/InventoryExamination.h"
#include "Widgets/Inventory/MainWidget/MainInventoryWidget.h"
#include "Widgets/Inventory/Grid/InventoryGridWidget.h"
#include "Widgets/Inventory/Slot/InventorySlotWidget.h"
#include "Widgets/Inventory/Exam/ExaminationWidget.h"
#include "Pickups/Base/PickupBase.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() : PlayerRef(nullptr), PC(nullptr), InventoryWidgetRef(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	ComponentSetup();
}

void UInventoryComponent::ComponentSetup()
{
	if (IsValid(PC))
	{
		InventoryItemsArray.SetNum(PC->GetInventorySlotsIndex());

		InventoryWidgetRef = PC->GetMainInventoryWidget();

		ExaminationWidgetRef = PC->GetExamWidget();
	}

	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInventoryExamination::StaticClass(), FoundActors);

	GEngine->AddOnScreenDebugMessage(-1, 8.F, FColor::White, L"Actor Name: " + FoundActors[0]->GetName());

	InventoryExaminationRef = Cast<AInventoryExamination>(FoundActors[0]);
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::CreateExaminationWidget(int32 InIndex)
{
	ExaminationWidgetRef->UpdateWidget(InIndex);

	InventoryWidgetRef->SetVisibility(ESlateVisibility::Collapsed);

	if (!ExaminationWidgetRef->IsInViewport())
		ExaminationWidgetRef->AddToViewport(2);
}

bool UInventoryComponent::AddItems(TSubclassOf<class AInventoryItemMaster> InItemSubclass, int32 InAmount, int32& OutRemainder)
{
	bool Success = false;

	int32 LocalIndex = 0;

	TObjectPtr<AInventoryItemMaster> LocalBaseClass = InItemSubclass.GetDefaultObject();

	const int32& LocalMaxStackAmount = LocalBaseClass->GetItemData().MaxStackAmount;

	if (LocalMaxStackAmount <= 1)
	{
		CheckForEmptySlot(LocalIndex, Success);

		if (Success)
		{
			InventoryItemsArray[LocalIndex].ItemSubclass = InItemSubclass;

			InventoryItemsArray[LocalIndex].Amount += 1;

			UpdateInventorySlot(LocalIndex);

			if (InAmount - 1 > 0)
			{
				int32 LocalRemainder = 0;

				AddItems(InItemSubclass, InAmount - 1, LocalRemainder);

				OutRemainder = LocalRemainder;

				return true;
			}

			else
			{
				OutRemainder = NULL;

				return true;
			}
		}
	}

	else if (LocalMaxStackAmount > 1)
	{
		CheckForFreeSlot(InItemSubclass, Success, LocalIndex);

		if (Success)
		{
			int32 LocalAmount = 0;

			GetItemAtIndex(LocalIndex, LocalAmount, InItemSubclass);

			if (LocalAmount + InAmount > LocalMaxStackAmount)
			{
				LocalAmount = (LocalAmount + InAmount) - LocalMaxStackAmount;

				InventoryItemsArray[LocalIndex].Amount = LocalMaxStackAmount;

				InventoryItemsArray[LocalIndex].ItemSubclass = InItemSubclass;

				UpdateInventorySlot(LocalIndex);

				AddItems(InItemSubclass, LocalAmount, OutRemainder);

				return true;
			}

			else
			{
				InventoryItemsArray[LocalIndex].Amount = LocalAmount + InAmount;

				InventoryItemsArray[LocalIndex].ItemSubclass = InItemSubclass;

				UpdateInventorySlot(LocalIndex);

				OutRemainder = NULL;

				return true;
			}
		}

		else if (!Success)
		{
			CheckForEmptySlot(LocalIndex, Success);

			if (InventoryItemsArray[LocalIndex].Amount > LocalMaxStackAmount)
			{
				int32 LocalRemainder = 0;

				InventoryItemsArray[LocalIndex].ItemSubclass = InItemSubclass;

				InventoryItemsArray[LocalIndex].Amount = LocalMaxStackAmount;

				UpdateInventorySlot(LocalIndex);

				AddItems(InItemSubclass, InAmount - LocalMaxStackAmount, LocalRemainder);

				OutRemainder = LocalRemainder;

				return true;
			}

			else if (InventoryItemsArray[LocalIndex].Amount < LocalMaxStackAmount)
			{
				InventoryItemsArray[LocalIndex].Amount = InAmount;

				InventoryItemsArray[LocalIndex].ItemSubclass = InItemSubclass;

				UpdateInventorySlot(LocalIndex);

				OutRemainder = NULL;

				return true;
			}

			else
			{
				CheckForEmptySlot(LocalIndex, Success);

				if (!Success)
				{
					OutRemainder = LocalIndex;

					return false;
				}
			}
		}
	}

	return false;
}

bool UInventoryComponent::RemoveItem(int32 InIndex)
{
	int32 LocalIndex = 0;

	TSubclassOf<AInventoryItemMaster> LocalOutItem = nullptr;

	GetItemAtIndex(InIndex, LocalIndex, LocalOutItem);

	if (LocalIndex > 0)
	{
		InventoryItemsArray[InIndex].ItemSubclass = LocalOutItem;

		InventoryItemsArray[InIndex].Amount = LocalIndex - 1;

		UpdateInventorySlot(InIndex);

		return true;
	}

	else
	{
		InventoryItemsArray[InIndex].ItemSubclass = nullptr;

		UpdateInventorySlot(InIndex);

		return false;
	}

	return false;
}

void UInventoryComponent::CheckForEmptySlot(int32& OutIndex, bool& IsSuccessful)
{
	for (int32 i = 0; i < InventoryItemsArray.Num(); ++i)
	{
		if (UKismetSystemLibrary::IsValidClass(InventoryItemsArray[i].ItemSubclass))
			IsSuccessful = false;
		
		else
		{
			IsSuccessful = true;

			OutIndex = i;

			break;
		}
	}
}

void UInventoryComponent::CheckForFreeSlot(TSubclassOf<class AInventoryItemMaster> InItemSubclass, bool& IsSuccessful, int32& OutIndex)
{
	for (int32 i = 0; i < InventoryItemsArray.Num(); ++i)
	{
		if (InventoryItemsArray[i].ItemSubclass == InItemSubclass && InventoryItemsArray[i].Amount < InItemSubclass.GetDefaultObject()->GetItemData().MaxStackAmount)
		{
			IsSuccessful = true;

			OutIndex = i;

			break;
		}
	}
}

void UInventoryComponent::GetItemAtIndex(int32 InIndex, int32& OutAmount, TSubclassOf<class AInventoryItemMaster>& OutItem)
{
	OutAmount = InventoryItemsArray[InIndex].Amount;

	OutItem = InventoryItemsArray[InIndex].ItemSubclass;
}

void UInventoryComponent::UpdateInventorySlot(int32 InIndex)
{
	if (!IsValid(PC))
		PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	else if (IsValid(PC))
		PC->GetMainInventoryWidget()->GridWidget->GetSlotsArray()[InIndex]->UpdateSlots();
}

void UInventoryComponent::UseItem(int32 InIndex)
{
	int32 LocalOutIndex = 0;

	FTransform LocalTransform = FTransform();

	TSubclassOf<AInventoryItemMaster> LocalOutItem = nullptr;

	GetItemAtIndex(InIndex, LocalOutIndex, LocalOutItem);

	if (LocalOutIndex > NULL)
	{
		TObjectPtr<AInventoryItemMaster> Item = Cast<AInventoryItemMaster>(UGameplayStatics::GetActorOfClass(GetWorld(), LocalOutItem));

		if (IsValid(Item))
		{
			Item->UseItem();

			if (Item->GetUseItemSucessfully())
			{
				RemoveItem(InIndex);
	
				if (IsValid(InventoryWidgetRef))
					InventoryWidgetRef->CloseDropDownMenu();
			}
		}

		else
		{
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			Item = GetWorld()->SpawnActor<AInventoryItemMaster>(LocalOutItem, LocalTransform, Params);

			if (IsValid(Item))
			{
				Item->UseItem();

				if (Item->GetUseItemSucessfully())
				{
					RemoveItem(InIndex);

					if (IsValid(InventoryWidgetRef))
						InventoryWidgetRef->CloseDropDownMenu();
				}
			}

			else
				return;
		}
	}
}

void UInventoryComponent::DropItem(int32 InIndex)
{
	int32 LocalAmount = 0;

	TSubclassOf<AInventoryItemMaster> LocalOutItem = nullptr;

	GetItemAtIndex(InIndex, LocalAmount, LocalOutItem);

	if (LocalAmount > NULL)
	{
		for (int32 i = 0; i < LocalAmount; ++i)
			RemoveItem(InIndex);

		if (IsValid(InventoryWidgetRef))
		{
			InventoryWidgetRef->CloseDropDownMenu();

			if (IsValid(PlayerRef))
			{
				FActorSpawnParameters Params;

				FVector Start{ PlayerRef->GetPlayerCamera()->GetComponentLocation() };
				FVector End{ (PlayerRef->GetPlayerCamera()->GetComponentRotation().Vector() * 200.F) + Start };
				FRotator Rotation{ PlayerRef->GetPlayerCamera()->GetComponentRotation() };

				FHitResult Result;

				const bool& bHasHitOccured = GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECollisionChannel::ECC_Visibility);

				TObjectPtr<APickupBase> PickupSpawn = nullptr;

				if (bHasHitOccured)
				{
					PickupSpawn = GetWorld()->SpawnActor<APickupBase>(LocalOutItem.GetDefaultObject()->GetItemData().PickupActor, Result.Location, Rotation, Params);

					if (IsValid(PickupSpawn))
					{
						PickupSpawn->SetAmount(LocalAmount);

						PickupSpawn->GetBaseMesh()->SetSimulatePhysics(true);
					}
				}

				else
				{
					PickupSpawn = GetWorld()->SpawnActor<APickupBase>(LocalOutItem.GetDefaultObject()->GetItemData().PickupActor, Result.TraceEnd, Rotation, Params);

					if (IsValid(PickupSpawn))
					{
						PickupSpawn->SetAmount(LocalAmount);

						PickupSpawn->GetBaseMesh()->SetSimulatePhysics(true);
					}
				}
			}
		}
	}
}

