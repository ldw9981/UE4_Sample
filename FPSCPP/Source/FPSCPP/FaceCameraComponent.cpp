// Fill out your copyright notice in the Description page of Project Settings.


#include "FaceCameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UFaceCameraComponent::UFaceCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFaceCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFaceCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (PlayerCameraManager != nullptr)
	{
		USceneComponent* RootComponent = PlayerCameraManager->GetRootComponent();
		if (RootComponent != nullptr)
		{
			SetWorldRotation(UKismetMathLibrary::MakeRotationFromAxes(RootComponent->GetForwardVector()*-1.0f, RootComponent->GetRightVector()*-1.0f, RootComponent->GetUpVector())); 
		}
	}
}

