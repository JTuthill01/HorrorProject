#include "Widgets/Progress/ProgressBarWidgets.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/Health/HealthComponent.h"
#include "Components/Movement/MovementComp.h"
#include "Components/Flashlight/FlashlightComponent.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

UProgressBarWidgets::UProgressBarWidgets(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UProgressBarWidgets::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Player = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	HealthBar->SetPercent(GetHealthPrecent());

	StaminaBar->SetPercent(GetStaminaPrecent());

	BatteryBar->SetPercent(GetBatteryPrecent());
}

void UProgressBarWidgets::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!Player.IsValid())
		return;

	HealthBar->SetPercent(GetHealthPrecent());

	StaminaBar->SetPercent(GetStaminaPrecent());

	BatteryBar->SetPercent(GetBatteryPrecent());
}

double UProgressBarWidgets::GetHealthPrecent()
{
	if (!Player.IsValid())
		return 0.0;

	return Player->GetHealthComponent()->GetCurrentHealth() / Player->GetHealthComponent()->GetMaxHealth();
}

double UProgressBarWidgets::GetStaminaPrecent()
{
	if (!Player.IsValid())
		return 0.0;

	return Player->GetMovementComp()->GetCurrentStamina() / Player->GetMovementComp()->GetMaxStamina();
}

double UProgressBarWidgets::GetBatteryPrecent()
{
	if (!Player.IsValid())
		return 0.0;

	return Player->GetFlashLightComp()->GetCurrentBatteryLevel() / Player->GetFlashLightComp()->GetMaxBatteryLevel();
}
