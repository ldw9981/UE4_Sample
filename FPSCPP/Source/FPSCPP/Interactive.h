// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"

class ACharacter;

// This class does not need to be modified.
// BP���� �����.
UINTERFACE(MinimalAPI,Blueprintable)
class UInteractive : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPSCPP_API IInteractive
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void BlueprintInteract(ACharacter* Player);

	virtual void NativeInteract(ACharacter* Player) 
	{
		UObject* Object = Cast<UObject>(this);
		if (Object)
		{
			// �⺻ �۵��� C++���� NativeInteract ȣ���� �ϸ� ��������Ʈ Interface ������ ȣ�� ���ش�.
			Execute_BlueprintInteract(Object, Player);
		}		
	}
};