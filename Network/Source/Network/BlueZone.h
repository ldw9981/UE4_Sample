// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlueZone.generated.h"


UCLASS()
class NETWORK_API ABlueZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	//ABlueZone();

	/** Constructor for AActor that takes an ObjectInitializer for backward compatibility */
	ABlueZone(const FObjectInitializer& ObjectInitializer);

private:
	/** Called from the constructor to initialize the class to its default settings */
	void InitializeDefaults();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlueZone")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float CurrentRadius = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float MeshRadius = 200;

	float DifferenceRadius = 0.0f;
	float MeshScaleTo1Unit = 0.0f;
	float TargetRadius = 0.0f;
	FVector TargetCenter;
	FVector CurrentCenter;
	float InterpSpeedRadius = 0.0f;
	float InterpSpeedCenter = 0.0f;
	float PhazeTime = 5.0f;
	bool bZoneMove = false;

	FTimerHandle PainTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetRadius(float NewRadius);
	void PainOutside();

	UFUNCTION(NetMulticast, Reliable)
	void S2A_SetZoneMovePhaze(float NewPageTime, FVector NewCenter, float NewTargetRadius);
	void S2A_SetZoneMovePhaze_Implementation(float NewPageTime, FVector NewCenter, float NewTargetRadius);

	UFUNCTION(NetMulticast, Reliable)
	void S2A_SetWaitPhaze(float NewPageTime);
	void S2A_SetWaitPhaze_Implementation(float NewPageTime);

	FVector GetRandomLocationInRadius(const FVector & Origin, const float Radius);

};
