// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlueZone.generated.h"

USTRUCT(BlueprintType)
struct NETWORK_API FBlueZonePhaze
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float DelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float PhazeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float PhazeRadius;

	FBlueZonePhaze()
		:DelayTime(0.0f)
		,PhazeTime(0.0f)
		,PhazeRadius(0.0f)
	{

	}
};

UCLASS()
class NETWORK_API ABlueZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlueZone();
private:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlueZone")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float CurrentRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float MeshRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	TArray<FBlueZonePhaze> PhazeInfos; 

	float DifferenceRadius = 0.0f;
	float MeshScaleTo1Unit = 0.0f;		// 1Unit 으로 만드는 스케일값
	float TargetRadius = 0.0f;
	FVector TargetCenter;
	FVector CurrentCenter;
	float InterpSpeedRadius = 0.0f;
	float InterpSpeedCenter = 0.0f;
	float PhazeTime;
	bool bZoneMove = false;
	int PhazeIndex;

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

	FVector GetLocationRandomCircle(const FVector & Origin, const float Radius);

};
