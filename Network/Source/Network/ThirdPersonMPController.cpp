// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonMPController.h"
#include "Engine/Engine.h"
#include "ThirdPersonMPCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Network.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "ThirdPersonMPGameState.h"




AThirdPersonMPController::AThirdPersonMPController()
{
	CurrentLife = 0;
	MaxLife = 2;
}

void AThirdPersonMPController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AThirdPersonMPController, CurrentLife);
}

void AThirdPersonMPController::BeginPlay()
{
	CurrentLife = MaxLife;
}

void AThirdPersonMPController::OnRep_Pawn()
{

}

void AThirdPersonMPController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

bool AThirdPersonMPController::DecreaseLife()
{
	if (CurrentLife<=0)
		return false;
	
	CurrentLife--;
	return true;
}

void AThirdPersonMPController::BeginPlayingState()
{
	Super::BeginPlayingState();
	if (HasAuthority())
	{		
		AThirdPersonMPGameState* GS = GetWorld()->GetGameState<AThirdPersonMPGameState>();
		GS->CurrentPlayingPlayerNum++;	
	}

}

void AThirdPersonMPController::EndPlayingState()
{	
	Super::EndPlayingState();

	if (HasAuthority())
	{
		AThirdPersonMPGameState* GS = GetWorld()->GetGameState<AThirdPersonMPGameState>();
		GS->CurrentPlayingPlayerNum--;
	}
}
