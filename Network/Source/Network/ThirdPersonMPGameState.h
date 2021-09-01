// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ThirdPersonMPGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotifyTimeSignature,int, Min);

/**
 * 
 */
UCLASS()
class NETWORK_API AThirdPersonMPGameState : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastBlueZoneNotifyTime(int Min);
	virtual void MulticastBlueZoneNotifyTime_Implementation(int Min);
};
