// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BillboardComponent.h"
#include "Engine/Texture2D.h"
#include "NavigationSystem.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	DefaultSceneRoot->SetMobility(EComponentMobility::Static);
	SetRootComponent(DefaultSceneRoot);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Radius"));
	Collision->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	Collision->SetupAttachment(RootComponent);
	Collision->SetMobility(EComponentMobility::Static);

	SpawnMax = 3;
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
void ASpawner::BeginPlay()
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
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawner::IsValidSettings()
{
	if (SpawnActorClass.Num() == 0)
	{
		return false;
	}

	for (int i=0;i< SpawnActorClass.Num();i++)
	{
		if ( SpawnActorClass[i] == NULL )
		{
			return false;
		}		
	}
	return true;
}

void ASpawner::OnSpawnActorDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason != EEndPlayReason::Destroyed)
		return;

	Destroy++;

	//Spawn();
	if (UseRespawn)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		if (TimerManager.IsTimerActive(SpawnTimer) == false)
		{
			TimerManager.SetTimer(SpawnTimer, this, &ASpawner::OnTimerSpawn, SpawnDelay, true);
		}
	}
	else if(Destroy >= SpawnMax  )
	{
		OnDestroyedAll.Broadcast();
	}
}

void ASpawner::OnTimerSpawn()
{
	if (Destroy > 0)
	{
		FVector SpawnLocation;
		Spawn(SpawnLocation);
		Destroy--;
		if (Destroy <= 0)
		{
			FTimerManager& TimerManager = GetWorld()->GetTimerManager();
			TimerManager.ClearTimer(SpawnTimer);
		}
	}
}

void ASpawner::GetSpawnLocation(FVector& out)
{
	bool result = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(
		GetWorld(),
		GetActorLocation(),
		out,
		Collision->GetScaledSphereRadius()
	);

	if (result == false)
	{
		out = GetActorLocation();
	}
}

void ASpawner::Spawn(const FVector& SpawnLocation)
{
	FRotator SpawnRotator;
	SpawnRotator.Pitch = 0.0f;
	SpawnRotator.Pitch = 0.0f;
	SpawnRotator.Yaw = 0.0f;

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	int index = FMath::RandHelper(SpawnActorClass.Num());
	AActor* Spawned  = GetWorld()->SpawnActor(SpawnActorClass[index],&SpawnLocation, &SpawnRotator,Param);
	if (Spawned)
	{
		
		Spawned->OnEndPlay.AddDynamic(this, &ASpawner::OnSpawnActorDestroyed);
	}
}

