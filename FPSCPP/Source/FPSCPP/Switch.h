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
		// C++���� ���ϴ� ó���� �����ϰ� 

		if (PointLight)
		{
			PointLight->SetActorHiddenInGame(!PointLight->IsHidden());
		}

		// ��� ����Ʈ������ �޼��� ������ ó���ϰ� �Ѵ�. 
		IInteractive::NativeInteract(Player);
	}	
};
