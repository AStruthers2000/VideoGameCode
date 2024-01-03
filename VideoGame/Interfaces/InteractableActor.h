#pragma once
#include "InteractableActor.generated.h"

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
};


