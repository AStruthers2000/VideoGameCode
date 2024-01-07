// Copyright Aurora Laboratories


#include "InteractionWidgetParent.h"

void UInteractionWidgetParent::UpdateTimerText(const float NewTime)
{
	//UE_LOG(LogTemp, Display, TEXT("%f"), NewTime);
	SetTimeRemainingText(NewTime);
}
