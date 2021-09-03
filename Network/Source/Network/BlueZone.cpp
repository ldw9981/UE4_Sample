// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueZone.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "ThirdPersonMPController.h"
#include "Network.h"

ABlueZone::ABlueZone()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AssetMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	Mesh->SetStaticMesh(AssetMesh.Object);	
	SetRootComponent(Mesh);

	MeshRadius = 50.f;
	DifferenceRadius = 0.0f;
	MeshScaleTo1Unit = 1.0f / MeshRadius;			// 1Unit 으로 만드는 스케일값
	TargetRadius = 0.0f;
	TargetCenter = FVector(0.0f,0.0f,0.0f);
	CurrentCenter = FVector(0.0f, 0.0f, 0.0f);
	InterpSpeedRadius = 0.0f;
	InterpSpeedCenter = 0.0f;
	PhazeTime = 5.0f;
	bZoneMove = false;
	PhazeIndex = 0;

	SetRadius(10000.0f);
}

// Called when the game starts or when spawned
void ABlueZone::BeginPlay()
{
	Super::BeginPlay();
	CurrentCenter = GetActorLocation();

	
	SetRadius(CurrentRadius);


	if (UKismetSystemLibrary::IsServer(GetWorld()))
	{
		//1초 주기
		GetWorld()->GetTimerManager().SetTimer(
			PainTimer,
			this,
			&ABlueZone::PainOutside,
			1.0f,
			true,
			0);
	}	
}

// Called every frame
void ABlueZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	AThirdPersonMPController* PC = Cast<AThirdPersonMPController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PhazeTime -= DeltaTime;
	if (PC && PC->IsLocalPlayerController())
	{
//		PC->UI_SetPhazeTime(PhazeTime);
	}


		if (PhazeTime <= 0.0f)
		{
			PhazeTime = 0;

			if (GetWorld()->IsServer())
			{
				if (!bZoneMove)
				{
					float PrevRadius = CurrentRadius;
					float NewRadius = CurrentRadius * 0.5f;
					FVector NewTargetCenter = GetLocationRandomCircle(CurrentCenter, PrevRadius - NewRadius);

					S2A_SetZoneMovePhaze(5, NewTargetCenter, NewRadius);
				}
				else
				{
					S2A_SetWaitPhaze(5);
				}
			}
		}

		if (bZoneMove)
		{
			CurrentRadius = FMath::FInterpConstantTo(CurrentRadius, TargetRadius, DeltaTime, InterpSpeedRadius);
			CurrentCenter = FMath::VInterpConstantTo(CurrentCenter, TargetCenter, DeltaTime, InterpSpeedCenter);
			SetRadius(CurrentRadius);
			SetActorLocation(CurrentCenter);

			// 이동중일때 갱신

			if (PC && PC->IsLocalPlayerController())
			{
				float Progress = 1 - ((CurrentRadius - TargetRadius) / DifferenceRadius);
				//PC->UI_SetSafeZoneProgress(Progress);
			}
		}

}

void ABlueZone::SetRadius(float NewRadius)
{
	FVector Scale(NewRadius*MeshScaleTo1Unit, NewRadius*MeshScaleTo1Unit, GetActorScale().Z);
	Mesh->SetWorldScale3D(Scale);
	CurrentRadius = NewRadius;
}

void ABlueZone::PainOutside()
{


	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		AThirdPersonMPController* PC = Cast<AThirdPersonMPController>(*Iter);
		if (!PC)
		{
			continue;
		}
		ACharacter* Character = Cast<ACharacter>(PC->GetPawn());
		if (!Character)
		{
			continue;
		}

		/*
		if (Character->IsDead())
		{
			continue;
		}
		*/


		FVector ActorLocationXY = Character->GetActorLocation();
		ActorLocationXY.Z = 0;
		FVector ZoneLocationXY = GetActorLocation();
		ZoneLocationXY.Z = 0;

		float Size = FVector(ActorLocationXY - ZoneLocationXY).Size();
		if ( Size <= CurrentRadius)
		{
			continue;
		}

		UGameplayStatics::ApplyDamage(Character, 1, nullptr, this, UDamageType::StaticClass());
	}

}



void ABlueZone::S2A_SetZoneMovePhaze_Implementation(float NewPageTime, FVector NewCenter, float NewTargetRadius)
{
	bZoneMove = true;
	PhazeTime = NewPageTime;
	TargetRadius = NewTargetRadius;
	TargetCenter = NewCenter;

	DifferenceRadius = (CurrentRadius - TargetRadius);
	InterpSpeedRadius = DifferenceRadius / PhazeTime;		// 1초에 줄어야할 반지름 크기	
	InterpSpeedCenter = FVector(TargetCenter - CurrentCenter).Size() / PhazeTime;	//1초에 이동해야할 크기
	
	if (HasAuthority())
	{
		UE_LOG(LogNetwork, Display, TEXT("%f,%f  %f,%f       %f, %f, %f"), CurrentCenter.X, CurrentCenter.Y, TargetCenter.X, TargetCenter.Y, CurrentRadius, TargetRadius, PhazeTime);
	}
	
	
//	UE_LOG(LogClass, Warning, TEXT("InterpSpeedRadius %f,InterpSpeedCenter %f"), InterpSpeedRadius, InterpSpeedCenter);
}

void ABlueZone::S2A_SetWaitPhaze_Implementation(float NewPageTime)
{
	bZoneMove = false;
	PhazeTime = NewPageTime;

	AThirdPersonMPController* PC = Cast<AThirdPersonMPController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->IsLocalPlayerController())
	{
//		PC->UI_SetSafeZoneProgress(0.0f);
	}
}

FVector ABlueZone::GetLocationRandomCircle(const FVector & Origin, const float Radius)
{
	const float RandomAngle = 2.f * PI * FMath::FRand();  /* 0.0 ~ 2PI.0 */

	const FVector RandomOffset(FMath::Cos(RandomAngle) * Radius, FMath::Sin(RandomAngle) * Radius, 0);
	FVector RandomLocationInRadius = Origin + RandomOffset;
	return RandomLocationInRadius;
}