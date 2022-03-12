// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSCPPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSCPP_API AFPSCPPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void PawnOnEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
