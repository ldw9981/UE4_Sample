// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerByTargetPoint.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BillboardComponent.h"
#include "Engine/Texture2D.h"
#include "NavigationSystem.h"
#include "Engine/TargetPoint.h"

// Sets default values
ASpawnerByTargetPoint::ASpawnerByTargetPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	DefaultSceneRoot->SetMobility(EComponentMobility::Static);
	SetRootComponent(DefaultSceneRoot);

	SpawnMax = 0;
	SpawnDelay = 3.0f;
	Destroy = 0;
	UseRespawn = true;

	// From TriggerBase.cpp
#if WITH_EDITORONLY_DATA	
	SpriteComponent = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
	if (SpriteComponent)
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureObject;
			FName ID;
			FText NAME;
			FConstructorStatics()
				: TextureObject(TEXT("/Engine/EditorResources/Spawn_Point"))
				, ID(TEXT("SpawnerByTargetPoint"))
				, NAME(NSLOCTEXT("SpriteCategory", "SpawnerByTargetPoint", "SpawnerByTargetPoint"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		SpriteComponent->Sprite = ConstructorStatics.TextureObject.Get();
		SpriteComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		SpriteComponent->bHiddenInGame = true;
		SpriteComponent->SpriteInfo.Category = ConstructorStatics.ID;
		SpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME;
		SpriteComponent->bIsScreenSizeScaled = true;

		SpriteComponent->SetupAttachment(RootComponent);
	}
#endif
}


// Called when the game starts or when spawned
void ASpawnerByTargetPoint::BeginPlay()
{
	Super::BeginPlay();
	FVector SpawnLocation;

	if (IsValidSettings() == true)
	{
		for (int i = 0; i < SpawnMax; i++)
		{

			GetSpawnLocation(SpawnLocation);
			Spawn(SpawnLocation);
		}
	}
}

// Called every frame
void ASpawnerByTargetPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawnerByTargetPoint::IsValidSettings()
{
	if (TargetPointClass==nullptr)
	{
		return false;
	}

	if (SpawnActorClass.Num() == 0)
	{
		return false;
	}

	for (int i = 0; i < SpawnActorClass.Num(); i++)
	{
		if (SpawnActorClass[i] == NULL)
		{
			return false;
		}
	}

	if (TargetPointClass == nullptr)
	{
		return false;
	}

	TArray<AActor*> ChildActors;
	AActor* Actor = GetAttachParentActor();
	if (Actor == nullptr)
	{
		Actor = this;
	}
	Actor->GetAttachedActors(ChildActors);
	for (AActor* A : ChildActors)
	{
		if (A->GetClass() == TargetPointClass)
		{
			SpawnLocationList.Add(A->GetActorLocation());
		}
	}

	if (SpawnLocationList.Num() == 0)
	{
		return false;
	}

	SpawnMax = SpawnLocationList.Num();
	return true;
}

void ASpawnerByTargetPoint::OnSpawnActorDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason != EEndPlayReason::Destroyed)
		return;

	Destroy++;
	SpawnLocationList.Add(Actor->GetActorLocation());

	//Spawn();
	if (UseRespawn)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		if (TimerManager.IsTimerActive(SpawnTimer) == false)
		{
			TimerManager.SetTimer(SpawnTimer, this, &ASpawnerByTargetPoint::OnTimerSpawn, SpawnDelay, true);
		}
	}
	else if (Destroy >= SpawnMax)
	{
		OnDestroyedAll.Broadcast();
	}
}

void ASpawnerByTargetPoint::OnTimerSpawn()
{
	if (Destroy > 0)
	{
		FVector SpawnLocation;
		GetSpawnLocation(SpawnLocation);
		Spawn(SpawnLocation);
		Destroy--;
		if (Destroy <= 0)
		{
			FTimerManager& TimerManager = GetWorld()->GetTimerManager();
			TimerManager.ClearTimer(SpawnTimer);
		}
	}
}

void ASpawnerByTargetPoint::GetSpawnLocation(FVector& out)
{
	if (SpawnLocationList.Num()==0)
	{
		return;
	}

	out = SpawnLocationList[0];
	SpawnLocationList.RemoveAt(0);
	
}

void ASpawnerByTargetPoint::Spawn(const FVector& SpawnLocation)
{
	FRotator SpawnRotator;
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	int index = FMath::RandHelper(SpawnActorClass.Num());
	AActor* Spawned = GetWorld()->SpawnActor(SpawnActorClass[index], &SpawnLocation, &SpawnRotator, Param);
	if (Spawned)
	{

		Spawned->OnEndPlay.AddDynamic(this, &ASpawnerByTargetPoint::OnSpawnActorDestroyed);
	}
}

