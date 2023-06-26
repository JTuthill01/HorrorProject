#pragma once
#include "Str_ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	FItemData() {};

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UClass> PickupActor = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UStaticMesh> ExamMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ItemName = FName(NAME_None);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ItemDescription = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UTexture2D> ItemIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxStackAmount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	double ExaminationMeshOffset = 20.0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bCanBeUsed = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bCanBeDropped = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bCanBeExamined = true;
};