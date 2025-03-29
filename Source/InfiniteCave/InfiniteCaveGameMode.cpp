// Copyright Epic Games, Inc. All Rights Reserved.

#include "InfiniteCaveGameMode.h"
#include "InfiniteCaveCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInfiniteCaveGameMode::AInfiniteCaveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
