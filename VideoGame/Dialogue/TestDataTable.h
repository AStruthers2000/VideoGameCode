// Copyright Aurora Laboratories

#pragma once

#include "CoreMinimal.h"
#include "DialogueData.h"
#include "Engine/DataTable.h"
#include "TestDataTable.generated.h"

USTRUCT(Blueprintable)
struct FDialogueRow : public FTableRowBase
{
	GENERATED_BODY();

public:

	///FDialogueRow() : DialogueNumber(0){};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Dialogue)
	int32 DialogueNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Dialogue)
	UDialogueData* Data;
};

/**
 * 
 */
UCLASS()
class VIDEOGAME_API UTestDataTable : public UDataTable
{
	GENERATED_BODY()
	
};
