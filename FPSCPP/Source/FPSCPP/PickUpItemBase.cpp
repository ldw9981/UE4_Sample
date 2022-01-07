// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APickUpItemBase::APickUpItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	SetRootComponent(DefaultSceneRoot);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpItemCollision"));
	Collision->SetupAttachment(DefaultSceneRoot);
	Collision->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	Collision->SetCollisionProfileName(FName(TEXT("Trigger")));

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpItemItemMesh"));
	ItemMesh->SetupAttachment(Collision);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickUpItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

