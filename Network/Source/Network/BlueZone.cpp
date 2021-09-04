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
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameState.h"

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

	CurrentCenter = FVector(0.0f, 0.0f, 0.0f);
	InterpSpeedRadius = 0.0f;
	InterpSpeedCenter = 0.0f;

	SetRadius(100.0f);
}

// Called when the game starts or when spawned
void ABlueZone::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentCenter = GetActorLocation();
	SetRadius(CurrentRadius);
	
	SetActorTickEnabled(false);	// 페이즈가 바뀔때 활성화한다.

	if (UKismetSystemLibrary::IsServer(GetWorld()))
	{		
		if (CommonInfos.Num()>0)
		{
			ServerInfo.PhazeIndex=0;
			ServerInfo.CircleCenter = GetLocationRandomCircle(CurrentCenter, CurrentRadius - CommonInfos[ServerInfo.PhazeIndex].CircleRadius);
			if (UpdateCurrentPhazeInfo())
			{
				SetActorTickEnabled(true);
			}		
		}	
		GetWorld()->GetTimerManager().SetTimer(PainTimer, this, &ABlueZone::PainOutside, 1.0f, true, 0); //1초 주기
	}
}

// Called every frame
void ABlueZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	float ServerTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	if (MoveCompleteTime<ServerTime)
	{
		SetActorTickEnabled(false);

		if (HasAuthority())
		{
			if (ServerInfo.PhazeIndex < CommonInfos.Num()-1)
			{
				ServerInfo.PhazeIndex++;
				ServerInfo.CircleCenter = GetLocationRandomCircle(CurrentCenter, CurrentRadius - CommonInfos[ServerInfo.PhazeIndex].CircleRadius);
				if (UpdateCurrentPhazeInfo())
				{
					SetActorTickEnabled(true);
				}
			}			
		}		
	}
	else if ((DelayCompleteTime < ServerTime) && (ServerTime <= MoveCompleteTime))
	{
		if (PrevServerTime > 0)
		{
			CurrentRadius = FMath::FInterpConstantTo(CurrentRadius, CommonInfos[ServerInfo.PhazeIndex].CircleRadius, ServerTime - PrevServerTime, InterpSpeedRadius);
			CurrentCenter = FMath::VInterpConstantTo(CurrentCenter, ServerInfo.CircleCenter, ServerTime - PrevServerTime, InterpSpeedCenter);
			SetRadius(CurrentRadius);
			SetActorLocation(CurrentCenter);
		}
	}	
	PrevServerTime = ServerTime;
	
	/*
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

					//S2A_SetZoneMovePhaze(5, NewTargetCenter, NewRadius);

				}
				else
				{
					//S2A_SetWaitPhaze(5);
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
		*/
}

void ABlueZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlueZone, ServerInfo);
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

		UGameplayStatics::ApplyDamage(Character, CommonInfos[ServerInfo.PhazeIndex].Damage, nullptr, this, UDamageType::StaticClass());
	}

}

FVector ABlueZone::GetLocationRandomCircle(const FVector & Origin, const float Radius)
{
	const float RandomAngle = 2.f * PI * FMath::FRand();  /* 0.0 ~ 2PI.0 */

	const FVector RandomOffset(FMath::Cos(RandomAngle) * Radius, FMath::Sin(RandomAngle) * Radius, 0);
	FVector RandomLocationInRadius = Origin + RandomOffset;
	return RandomLocationInRadius;
}

void ABlueZone::OnRep_PhazeInfo()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("OnRep_PhazeInfo"));	
	if (UpdateCurrentPhazeInfo())
	{		
		SetActorTickEnabled(true);
	}
}

bool ABlueZone::UpdateCurrentPhazeInfo()
{
	int index = ServerInfo.PhazeIndex;	
	if (index >= CommonInfos.Num())
	{
		return false;
	}

	float StartTime = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	DelayCompleteTime = StartTime + CommonInfos[index].DelayDuration;
	MoveCompleteTime = DelayCompleteTime + CommonInfos[index].MoveDuration;

	DifferenceRadius = (CurrentRadius - CommonInfos[index].CircleRadius);
	InterpSpeedRadius = DifferenceRadius / CommonInfos[index].MoveDuration;		// 1초에 줄어야할 반지름 크기	
	InterpSpeedCenter = FVector(ServerInfo.CircleCenter - CurrentCenter).Size() / CommonInfos[index].MoveDuration;	//1초에 이동해야할 크기	
	return true;
}
