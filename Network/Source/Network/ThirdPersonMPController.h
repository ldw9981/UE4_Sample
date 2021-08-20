// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonMPController.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API AThirdPersonMPController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(Category = "Controller")
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Category = "Controller")
	void OnEndPlayPawn( AActor* Actor, EEndPlayReason::Type EndPlayReason);
};
