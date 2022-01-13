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

	// C++에서 구현과 호출을 하고 BP에서 재정의 가능 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(ACharacter* Player);
	virtual void Interact_Implementation(ACharacter* Player) = 0;
};
