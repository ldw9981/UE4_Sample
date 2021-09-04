// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlueZone.generated.h"

USTRUCT(BlueprintType)
struct NETWORK_API FBlueZoneCommonInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float DelayDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float MoveDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float CircleRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlueZone")
	float Damage;

	FBlueZoneCommonInfo()
		: DelayDuration(0.0f)
		, MoveDuration(0.0f)
		, CircleRadius(0.0f)
		, Damage(1.0f)
	{

	}
};

USTRUCT(BlueprintType)
struct NETWORK_API FBlueZoneServerInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BlueZone")
	int PhazeIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlueZone")
	FVector CircleCenter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlueZone")
	float StartTime;

	FBlueZoneServerInfo()
		: PhazeIndex(-1)
		, CircleCenter(0.0f, 0.0f, 0.0f)
		, StartTime(0.0f)
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
	TArray<FBlueZoneCommonInfo> CommonInfos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlueZone", ReplicatedUsing = OnRep_PhazeInfo)
	FBlueZoneServerInfo ServerInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlueZone")
	float BlueProgress;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlueZone")
	float RemainTime;

	float DelayCompleteTime;	// 대기 완료 시간
	float MoveCompleteTime;		// 이동 완료 시간
	float PrevServerTime;

	float DifferenceRadius;
	float MeshScaleTo1Unit;		// 1Unit 으로 만드는 스케일값

	FVector CurrentCenter;
	float InterpSpeedRadius;
	float InterpSpeedCenter;

	FTimerHandle PainTimer;
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void SetRadius(float NewRadius);
	void PainOutside();
	FVector GetLocationRandomCircle(const FVector & Origin, const float Radius);
	
	UFUNCTION()
	void OnRep_PhazeInfo();

	bool UpdateCurrentPhazeInfo();
};
