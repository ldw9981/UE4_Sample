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
	
	// 위젯에 AbilityStat의 인스턴스를 업데이트 해줘야 해서 다시 위젯을 만든다.
	if (UKismetSystemLibrary::IsValidClass(HUDClass))
	{
		HUDReference = CreateWidget<UUserWidget>(this, HUDClass);
		if (HUDReference != nullptr)
		{
			IWidgetBindInterface::Execute_BindSource(HUDReference, InPawn);
			HUDReference->AddToViewport();
		}
	}	
}

// 캐릭터 없어질때 해야할것
void AFPSCPPPlayerController::PawnOnEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	// 캐릭터가 없어지면 AbilityStat이 무효화 되므로 Widget제거한다.
	if (HUDReference)
	{
		HUDReference->RemoveFromParent();
	}

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
