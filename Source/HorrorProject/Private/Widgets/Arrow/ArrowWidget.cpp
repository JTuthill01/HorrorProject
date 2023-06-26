#include "Widgets/Arrow/ArrowWidget.h"
#include "Dials/LockDial.h"
#include "Components/Button.h"

UArrowWidget::UArrowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), bAddRotation(true)
{
}

void UArrowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ArrowButton->OnClicked.AddDynamic(this, &UArrowWidget::AddRotation);
}

void UArrowWidget::AddRotation()
{
	if (bAddRotation)
	{
		if (IsValid(LockDialRef))
			LockDialRef->RotateDialForwards();
	}

	else
	{
		if (IsValid(LockDialRef))
			LockDialRef->RotateDialBackwards();
	}
}

void UArrowWidget::Init(ALockDial* InDial, bool InRotation)
{
	LockDialRef = InDial;

	bAddRotation = InRotation;
}
