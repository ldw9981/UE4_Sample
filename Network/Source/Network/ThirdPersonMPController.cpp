// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonMPController.h"
#include "Engine/Engine.h"
#include "ThirdPersonMPCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Network.h"

void AThirdPersonMPController::OnPossess(APawn* InPawn)
{	
	Super::OnPossess(InPawn);
	/*	
	if (HasAuthority())
	{
		InPawn->OnEndPlay.AddDynamic(this, &AThirdPersonMPController::OnEndPlayPawn);		
	}
	*/
}

void AThirdPersonMPController::OnEndPlayPawn(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{	
	/*
	if (HasAuthority())
	{
		FVector spawnLocation = Actor->GetActorLocation();
		FRotator spawnRotation = Actor->GetActorRotation();
		APawn* spawned = GetWorld()->SpawnActor<APawn>(GetWorld()->GetAuthGameMode()->DefaultPawnClass, spawnLocation, spawnRotation);
		if (spawned)
			return;

		Possess(spawned);	
		//UE_LOG(LogNetwork, Display, TEXT("OnEndPlayPawn %d %d"), GetNetMode(), GetLocalRole());
	}	
	*/
}
