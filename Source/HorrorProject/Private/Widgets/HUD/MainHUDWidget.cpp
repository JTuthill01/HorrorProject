#include "Widgets/HUD/MainHUDWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Widgets/Progress/ProgressBarWidgets.h"
#include "Kismet/GameplayStatics.h"

UMainHUDWidget::UMainHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
