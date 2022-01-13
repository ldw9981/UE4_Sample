// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Interactive.h"
#include "InteractiveOnlyCpp.h"
#include "Engine/PointLight.h"
#include "Switch.generated.h"

class APointLight;
/**
 * 
 */
UCLASS()
class FPSCPP_API ASwitch : public ATriggerBox, public IInteractive , public IInteractiveOnlyCpp
{
	GENERATED_BODY()
public:
	ASwitch()
	{		
		SetActorHiddenInGame(false);
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch");
	APointLight* PointLight;

	virtual void InteractOnlyCpp(ACharacter* Player)
	{
		NativeInteract(Player);
	}

	virtual void Interact_Implementation(ACharacter* Player)
	{
		NativeInteract(Player);
	}

	UFUNCTION(BlueprintCallable)
	virtual void NativeInteract(ACharacter* Player)
	{
		if (PointLight)
		{
			PointLight->SetActorHiddenInGame(!PointLight->IsHidden());
		}
	}	
};
