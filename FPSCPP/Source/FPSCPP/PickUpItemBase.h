// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpItemBase.generated.h"


class UStaticMeshComponent;
class USphereComponent;
class USceneComponent;

UCLASS()
class FPSCPP_API APickUpItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpItemBase();

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = PickUpItem)
	USceneComponent* DefaultSceneRoot;	

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = PickUpItem)
	USphereComponent* Collision;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = PickUpItem)
	UStaticMeshComponent* ItemMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnBeginOverlaped();
};
