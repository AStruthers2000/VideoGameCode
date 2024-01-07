// Copyright Aurora Laboratories

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidgetParent.generated.h"

/**
 * 
 */
UCLASS()
class VIDEOGAME_API UInteractionWidgetParent : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateTimerText(float NewTime);

	UFUNCTION(BlueprintImplementableEvent)
	void SetTimeRemainingText(float NewTime);
};
