// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "NavigationSystem.h"
#include "AbilityStatComponent.h"
#include "Components/TextRenderComponent.h"
#include "FaceCameraComponent.h"
#include "Bindable.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "HealthWidget.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MoveRadius = 500.0f;
	MoveDelay = 1.0f;
	AbilityStat = CreateDefaultSubobject<UAbilityStatComponent>("AbilityStat");
	
	FaceCamera = CreateDefaultSubobject<UFaceCameraComponent>("FaceCamera");
	FaceCamera->SetupAttachment(RootComponent);

	Widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	Widget->SetupAttachment(FaceCamera);
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	UHealthWidget* HealthWidget = Cast<UHealthWidget>(Widget->GetUserWidgetObject());
	if (HealthWidget !=nullptr)
	{
		HealthWidget->Bind(AbilityStat);
	}	

	AbilityStat->OnChangeHealth.AddDynamic(this, &AMonsterCharacter::OnChangeHealth);
	AbilityStat->ResetHealth();

	StartLocation = GetActorLocation();
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->ReceiveMoveCompleted.AddDynamic(this, &AMonsterCharacter::OnMoveCompleted);
		MoveAround();
	}

}

void AMonsterCharacter::MoveAround()
{
	if (AbilityStat->IsDead())
	{
		return;
	}

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
	if (AbilityStat->IsDead())
	{
		return;
	}
	
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMonsterCharacter::MoveAround, MoveDelay, false);
	
}


void AMonsterCharacter::OnChangeHealth(float Prev, float Curr)
{
	/*
	FText Number = FText::AsNumber(Curr);
	TextRender->SetText(Number);
	*/
	if (AbilityStat->IsDead())
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			AIController->StopMovement();

		}
		
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

