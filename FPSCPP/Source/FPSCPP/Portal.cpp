// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Character.h"

// Sets default values
APortal::APortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefaultSceneRoot");
	DefaultSceneRoot->SetMobility(EComponentMobility::Static);
	SetRootComponent(DefaultSceneRoot);
	
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(FName("Trigger"));
	Collision->SetupAttachment(RootComponent);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(FName("NoCollision"));
	Mesh->SetupAttachment(RootComponent);
	OnActorBeginOverlap.AddDynamic(this, &APortal::Work);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortal::Work(AActor* OverlappedActor, AActor* OtherActor)
{	
	if( OtherActor != UGameplayStatics::GetPlayerCharacter(GetWorld(),0) )
		return;

	FString Option;

	if( GameModeSoftClass.IsValid() )
	{
		Option = FString::Printf(TEXT("?game=%s"), *GameModeSoftClass.ToString());
	}
	UGameplayStatics::OpenLevel(GetWorld(), LevelName,true, Option);
}