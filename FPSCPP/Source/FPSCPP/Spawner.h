// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestoryedAll_SN);

class USphereComponent;
class UBillboardComponent;

UCLASS()
class FPSCPP_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleDefaultsOnly,Category = Spawn)
	USphereComponent* Collision;

	UPROPERTY(VisibleDefaultsOnly, Category = Spawn)
	UBillboardComponent* SpriteComponent;

	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<TSubclassOf<AActor>> SpawnActorClass;

	UPROPERTY(EditAnywhere, Category = Spawn)
	int SpawnMax;
		
	int Destroy;

	UPROPERTY(EditAnywhere, Category = Spawn)
	float SpawnDelay;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, Category = Spawn)
	bool UseRespawn;

	UPROPERTY(BlueprintAssignable, Category = Spawn)
	FOnDestoryedAll_SN OnDestroyedAll;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsValidSettings();
	void Spawn(const FVector& SpawnLocation);

	UFUNCTION()
	void OnSpawnActorDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason);

	void OnTimerSpawn();

	void GetSpawnLocation(FVector& out);
};
