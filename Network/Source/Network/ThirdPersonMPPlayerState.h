// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ThirdPersonMPPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API AThirdPersonMPPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AThirdPersonMPPlayerState();
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score", ReplicatedUsing = OnRep_KDA)
	int Kill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score", ReplicatedUsing = OnRep_KDA)
	int Death;

protected:
	UFUNCTION()
	void OnRep_KDA();

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
