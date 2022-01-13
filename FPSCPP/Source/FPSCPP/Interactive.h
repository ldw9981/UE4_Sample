// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"


// This class does not need to be modified.
// BP에서 사용함.
UINTERFACE(MinimalAPI,Blueprintable)
class UInteractive : public UInterface
{
	GENERATED_BODY()
};

/**
 *  C++,Blueprint 에서 모두 사용할수 있는 인터페이스 클래스
 *	C++호출은 IInteractive::Execute_Interact( 구현된액터, 다른인자들) 사용 , 
 *  BP에서 실행은 인터페이이스 메세지 Interact 사용한다.
 */
class FPSCPP_API IInteractive
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:		
	// BP에서 재구현이 없다면 Implementation 의 내용이 작동
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(ACharacter* Player);	  
	virtual void Interact_Implementation(ACharacter* Player) = 0;
};
