// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WidgetBindInterface.h"
#include "FPSCPPHUD.generated.h"

UCLASS()
class AFPSCPPHUD : public AHUD, public IWidgetBindInterface
{
	GENERATED_BODY()

public:
	AFPSCPPHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = HUD)
	UUserWidget* HUDWidgetRef;
private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void WidgetBindActor_Implementation(AActor* Source);
	virtual void WidgetBindComponent_Implementation(UActorComponent* Source);
};

