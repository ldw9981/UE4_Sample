// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ThirdPersonMPPlayerState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnKDASignature, AThirdPersonMPPlayerState*,PlayerState, int, Kill, int, Death);

UCLASS()
class NETWORK_API AThirdPersonMPPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AThirdPersonMPPlayerState();
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score", ReplicatedUsing = OnRep_Kill)
	int Kill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score", ReplicatedUsing = OnRep_Death)
	int Death;

	UPROPERTY(EditAnywhere, Category = "Score", BlueprintAssignable)
	FOnKDASignature OnKDA;

protected:
	UFUNCTION()
	void OnRep_Kill();
	UFUNCTION()
	void OnRep_Death();

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
