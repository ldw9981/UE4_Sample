// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WidgetBindInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable)
class UWidgetBindInterface : public UInterface
{
	GENERATED_BODY()
};


class AActor;
class UActorComponent;

/**
 * 
 */
class FPSCPP_API IWidgetBindInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void WidgetBindActor(AActor* Source);
	virtual void WidgetBindActor_Implementation(AActor* Source) = 0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void WidgetBindComponent(UActorComponent* Source);
	virtual void WidgetBindComponent_Implementation(UActorComponent* Source) = 0;
};
