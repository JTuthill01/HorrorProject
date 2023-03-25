#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerRefInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerRefInterface : public UInterface
{
	GENERATED_BODY()
};

class HORRORPROJECT_API IPlayerRefInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class APlayerCharacter* GetPlayerRef();
};
