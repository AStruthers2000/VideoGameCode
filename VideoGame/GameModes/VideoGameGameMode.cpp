// Copyright Epic Games, Inc. All Rights Reserved.

#include "VideoGameGameMode.h"
#include "../Player/VideoGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVideoGameGameMode::AVideoGameGameMode()
{
	// set default pawn class to our Blueprinted character
	/*
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/
}
