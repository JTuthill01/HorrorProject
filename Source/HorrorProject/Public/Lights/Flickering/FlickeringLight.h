#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlickeringLight.generated.h"

UCLASS()
class HORRORPROJECT_API AFlickeringLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlickeringLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ChangeIntensity();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LightSource, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPointLightComponent> Light;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Variables, meta = (AllowPrivateAccess = "true"))
	float Intensity;

private:
	float IntensityTimer;
	float MinTime;
	float MaxTime;

	bool bIsA;
	bool bIsB;

	FTimerHandle IntensityTimerHandle;
};
