// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveOnlyCpp.generated.h"

class ACharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveOnlyCpp : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class FPSCPP_API IInteractiveOnlyCpp
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InteractOnlyCpp(ACharacter* Player) = 0;
};
