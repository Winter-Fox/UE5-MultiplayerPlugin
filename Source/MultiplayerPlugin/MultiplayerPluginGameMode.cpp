// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerPluginGameMode.h"
#include "MultiplayerPluginCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerPluginGameMode::AMultiplayerPluginGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
