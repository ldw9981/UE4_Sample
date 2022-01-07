// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "NavigationSystem.h"
#include "AbilityStatComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MoveRadius = 500.0f;
	MoveDelay = 1.0f;
	AbilityStat = CreateDefaultSubobject<UAbilityStatComponent>("AbilityStat");
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->ReceiveMoveCompleted.AddDynamic(this,&AMonsterCharacter::OnMoveCompleted);
		MoveToAround();
	}

	AbilityStat->OnChangeHealth.AddDynamic(this, &AMonsterCharacter::OnChangeHealth);
	AbilityStat->ResetHealth();
}

void AMonsterCharacter::MoveToAround()
{
	FVector NewLocation;
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(GetWorld(), StartLocation, NewLocation,MoveRadius);
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->MoveToLocation(NewLocation);
	}
}

void AMonsterCharacter::DestroyDelayed()
{
	Destroy();
}

void AMonsterCharacter::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMonsterCharacter::MoveToAround, MoveDelay,false);
}


void AMonsterCharacter::OnChangeHealth(float Prev, float Curr)
{
	FText Number = FText::AsNumber(Curr);
	TextRender->SetText(Number);

	if (Curr <= 0.0f)
	{
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMonsterCharacter::DestroyDelayed, 3, false);
	}
}

// Called every frame
void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

