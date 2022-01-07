// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCPPGameMode.h"
#include "FPSCPPHUD.h"
#include "FPSCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSCPPGameMode::AFPSCPPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/BP_FirstPersonController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSCPPHUD::StaticClass();
}
