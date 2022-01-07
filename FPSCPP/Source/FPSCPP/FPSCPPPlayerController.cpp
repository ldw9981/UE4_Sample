// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCPPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

void AFPSCPPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	InPawn->OnEndPlay.AddDynamic(this,&AFPSCPPPlayerController::PawnOnEndPlay);
}

void AFPSCPPPlayerController::PawnOnEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason !=  EEndPlayReason::Destroyed)
		return;

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	if (GameModeBase)
	{		
		/** Tries to spawn the player's pawn, at the location returned by FindPlayerStart */
		// void RestartPlayer(AController* NewPlayer);
		// NewPlayer는 리스폰할 대상의 컨트롤러
		GameModeBase->RestartPlayer(this);
	}
}
