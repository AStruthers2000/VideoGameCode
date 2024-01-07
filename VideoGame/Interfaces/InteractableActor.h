#pragma once
#include "InteractableActor.generated.h"

class UWidgetComponent;

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractableActor : public UInterface
{
	GENERATED_BODY()
};

class IInteractableActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetVisibility_InteractUI(bool NewVisibility);
};


