// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"


class UAbilityStatComponent;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class FPSCPP_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	UMonsterAnimInstance();
protected:
	UAbilityStatComponent* AbilityStat;
	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
