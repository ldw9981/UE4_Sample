// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AActor;
class AGameModeBase;

UCLASS()
class FPSCPP_API APortal : public AActor
{
	GENERATED_BODY()
	
public:    
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Portal )
    UBoxComponent* Collision;
    
	UPROPERTY(Category = Portal, VisibleDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	FName	LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	TSoftClassPtr<AGameModeBase> GameModeSoftClass;

public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Work(AActor* OverlappedActor, AActor* OtherActor);

};
