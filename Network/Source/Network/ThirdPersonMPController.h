// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonMPController.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class NETWORK_API AThirdPersonMPController : public APlayerController
{
	GENERATED_BODY()
public:
	AThirdPersonMPController();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GamePlay", Replicated)
	int CurrentLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
	int MaxLife;

public:
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void OnRep_Pawn() override;
	virtual void OnPossess(APawn* aPawn) override;
	bool DecreaseLife();

	virtual void BeginPlayingState() override;
	virtual void EndPlayingState() override;
};
