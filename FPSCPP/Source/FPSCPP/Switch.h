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
		Interact_Implementation(Player);
	}

	// 기본 구현을 BP에서도 호출 가능하게 한다.
	UFUNCTION(BlueprintCallable)
	virtual void Interact_Implementation(ACharacter* Player)
	{
		if (PointLight)
		{
			PointLight->SetActorHiddenInGame(!PointLight->IsHidden());
		}
	}
};
