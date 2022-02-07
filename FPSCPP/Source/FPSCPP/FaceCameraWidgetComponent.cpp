// Fill out your copyright notice in the Description page of Project Settings.


#include "FaceCameraWidgetComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UFaceCameraWidgetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

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
