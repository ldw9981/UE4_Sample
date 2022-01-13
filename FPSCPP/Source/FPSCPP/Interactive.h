// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"

class ACharacter;

// This class does not need to be modified.
// BP에서 사용함.
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
			// 기본 작동은 C++에서 NativeInteract 호출을 하면 블루프린트 Interface 구현을 호출 해준다.
			Execute_BlueprintInteract(Object, Player);
		}		
	}
};
