#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "LockDial.generated.h"

UCLASS()
class HORRORPROJECT_API ALockDial : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE int32 GetDisplayNumber() const { return DisplayNumber; }

	FORCEINLINE void SetIndex(int32 InIndex) { Index = InIndex; }
	FORCEINLINE void SetLockRef(class ALock* Ref) { LockRef = Ref; }
	
public:	
	// Sets default values for this actor's properties
	ALockDial();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void FindNumber();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void RotateDial();

	UFUNCTION()
	void SetDialState();

public:
	void RotateDialBackwards();

	void RotateDialForwards();

private:
	void InitializeDial();

	void SetRandomNumber();

	void WidgetSetup();

private:
	UPROPERTY()
	TObjectPtr<class UArrowWidget> UpArrowWidget;

	UPROPERTY()
	TObjectPtr<class UArrowWidget> DownArrowWidget;

	UPROPERTY()
	TObjectPtr<class ALock> LockRef;

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> UpArrowWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> DownArrowWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> LockDialRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> LockDialMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FloatCurve, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCurveFloat> DialCurve;

private:
	int32 Index;
	int32 DisplayNumber;

	double DialRotation;
	double CurveFloatValue;
	double TimelineValue;
	double Alpha;
	double NegativeAlpha;
	double DialTimer;

	bool bCanRotate;

	FTimeline DialTimeline;
	FTimerHandle DialTimerHandle;
};

