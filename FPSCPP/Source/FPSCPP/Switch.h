// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Interactive.h"
#include "Engine/PointLight.h"
#include "Switch.generated.h"

class APointLight;
/**
 * 
 */
UCLASS()
class FPSCPP_API ASwitch : public ATriggerBox, public IInteractive
{
	GENERATED_BODY()
public:
	ASwitch()
	{		
		SetActorHiddenInGame(false);
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch");
	APointLight* PointLight;

	virtual void NativeInteract(ACharacter* Player) 
	{
		// C++에서 원하는 처리를 먼저하고 

		if (PointLight)
		{
			PointLight->SetActorHiddenInGame(!PointLight->IsHidden());
		}

		// 블루 프린트에서의 메세지 응답을 처리하게 한다. 
		IInteractive::NativeInteract(Player);
	}	
};
