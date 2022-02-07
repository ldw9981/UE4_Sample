// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "MonsterCharacter.generated.h"

class UAbilityStatComponent;
class UTextRenderComponent;
class UFaceCameraWidgetComponent;

UCLASS()
class FPSCPP_API AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Monster)
	UAbilityStatComponent* AbilityStat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Monster)
	UTextRenderComponent* TextRender;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Monster)
	UFaceCameraWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Monster)
	FVector StartLocation;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Monster)
	float	MoveRadius;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category=Monster)
	float	MoveDelay;
public:
	// Sets default values for this character's properties
	AMonsterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveAround();
	void DestroyDelayed();

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	UFUNCTION()
	void OnChangeHealth(float Prev,float Curr);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
