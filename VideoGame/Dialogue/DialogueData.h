// Copyright Aurora Laboratories

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class VIDEOGAME_API UDialogueData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Dialogue)
	TArray<FString> Lines;
	
};
