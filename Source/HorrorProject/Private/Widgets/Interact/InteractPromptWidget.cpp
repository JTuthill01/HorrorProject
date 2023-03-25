#include "Widgets/Interact/InteractPromptWidget.h"

UInteractPromptWidget::UInteractPromptWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UInteractPromptWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScreenSize = FVector2D((GetScreenSize().X / 2) , (GetScreenSize().Y / 2));

	//SetPositionInViewport(ScreenSize);
}

FVector2D UInteractPromptWidget::GetScreenSize()
{
	FVector2D Result = FVector2D(0.F);

	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(Result);

	return Result;
}
