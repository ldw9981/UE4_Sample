// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCPPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBindInterface.h"

// 캐릭터 스폰후  해야할것
void AFPSCPPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn->OnEndPlay.IsAlreadyBound(this, &AFPSCPPPlayerController::PawnOnEndPlay) == false)
	{
		InPawn->OnEndPlay.AddDynamic(this, &AFPSCPPPlayerController::PawnOnEndPlay);
	}

}

// 캐릭터 없어질때 해야할것
void AFPSCPPPlayerController::PawnOnEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	/** Actor가 명시적으로 파괴된 경우 */
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		if (GameModeBase)
		{
			/** Tries to spawn the player's pawn, at the location returned by FindPlayerStart */
			// void RestartPlayer(AController* NewPlayer);
			// NewPlayer는 리스폰할 대상의 컨트롤러
			GameModeBase->RestartPlayer(this);
		}
	}
}

void AFPSCPPPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
