// Copyright Epic Games, Inc. All Rights Reserved.

#include "GladiatorsGameMode.h"
#include "GladiatorsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGladiatorsGameMode::AGladiatorsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
