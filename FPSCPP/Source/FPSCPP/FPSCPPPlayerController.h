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
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TSubclassOf<class UUserWidget> HUDClass;

	UUserWidget* HUDReference;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void PawnOnEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);
};
