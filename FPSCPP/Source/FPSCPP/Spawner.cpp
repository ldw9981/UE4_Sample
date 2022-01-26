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
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Radius"));
	Collision->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	SetRootComponent(Collision);

	SpawnMax = 3;
	SpawnDelay = 3.0f;
	SpawnCount = 0;
	UseRespawn = true;

	// From TriggerBase.cpp
#if WITH_EDITORONLY_DATA	
	SpriteComponent = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
	if (SpriteComponent)
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> TriggerTextureObject;
			FName ID_Triggers;
			FText NAME_Triggers;
			FConstructorStatics()
				: TriggerTextureObject(TEXT("/Engine/EditorResources/Spawn_Point"))
				, ID_Triggers(TEXT("Triggers"))
				, NAME_Triggers(NSLOCTEXT("SpriteCategory", "Triggers", "Triggers"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		SpriteComponent->Sprite = ConstructorStatics.TriggerTextureObject.Get();
		SpriteComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		SpriteComponent->bHiddenInGame = true;
		SpriteComponent->SpriteInfo.Category = ConstructorStatics.ID_Triggers;
		SpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_Triggers;
		SpriteComponent->bIsScreenSizeScaled = true;

		SpriteComponent->SetupAttachment(Collision);
	}
#endif
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValidSpawnActorClass() == true)
	{
		for (int i = 0; i < SpawnMax; i++)
		{
			Spawn();
		}
	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawner::IsValidSpawnActorClass()
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

	SpawnCount--;

	//Spawn();
	if (UseRespawn)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		if (TimerManager.IsTimerActive(SpawnTimer) == false)
		{
			TimerManager.SetTimer(SpawnTimer, this, &ASpawner::OnTimerSpawn, SpawnDelay, true);
		}
	}
	else if(SpawnCount == 0)
	{
		OnDestroyedAll.Broadcast();
	}
}

void ASpawner::OnTimerSpawn()
{
	Spawn();

	if (SpawnCount >= SpawnMax)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(SpawnTimer);
	}
}

void ASpawner::Spawn()
{
	FVector SpawnLocation;
	FRotator SpawnRotator;

	bool result = UNavigationSystemV1::K2_GetRandomReachablePointInRadius(
		GetWorld(),
		GetActorLocation(),
		SpawnLocation,
		Collision->GetScaledSphereRadius()
	);

	if (result==false)
	{
		SpawnLocation = GetActorLocation();
	}

	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	int index = FMath::RandHelper(SpawnActorClass.Num());
	AActor* Spawned  = GetWorld()->SpawnActor(SpawnActorClass[index],&SpawnLocation, &SpawnRotator,Param);
	if (Spawned)
	{
		SpawnCount++;
		Spawned->OnEndPlay.AddDynamic(this, &ASpawner::OnSpawnActorDestroyed);
	}
}

