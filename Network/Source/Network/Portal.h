// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/DataTable.h"
#include "Portal.generated.h"




class UDataTable;

USTRUCT(BlueprintType)
struct FPortalInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TravelURL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETravelType> TravelType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSeamless;
};

class AActor;
/**
 * 
 */
UCLASS(Blueprintable)
class NETWORK_API APortal : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	//const FString& URL, ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid)

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString TravelURL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETravelType> TravelType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSeamless;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> PortalDataTableSOPtr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PortalIndex = 0;


public:
	APortal();

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor,AActor* OtherActor );
};
