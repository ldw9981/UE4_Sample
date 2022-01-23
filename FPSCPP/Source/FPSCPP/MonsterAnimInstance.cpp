// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "AbilityStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


UMonsterAnimInstance::UMonsterAnimInstance()
{
	Health = 100.0f;
	Speed = 0.0f;
}

void UMonsterAnimInstance::NativeBeginPlay()
{
	AActor* Actor = GetOwningActor();

	if (!Actor)
		return;

	AbilityStat = Cast<UAbilityStatComponent>(Actor->GetComponentByClass(UAbilityStatComponent::StaticClass()));
	CharacterMovement = Cast<UCharacterMovementComponent>(Actor->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
}


void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (AbilityStat)
	{
		Health = AbilityStat->Health;
	}

	if (CharacterMovement)
	{
		Speed = UKismetMathLibrary::VSize(CharacterMovement->Velocity);
	}
}


