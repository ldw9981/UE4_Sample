// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCPPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBindInterface.h"

// ĳ���� ������  �ؾ��Ұ�
void AFPSCPPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn->OnEndPlay.IsAlreadyBound(this, &AFPSCPPPlayerController::PawnOnEndPlay) == false)
	{
		InPawn->OnEndPlay.AddDynamic(this, &AFPSCPPPlayerController::PawnOnEndPlay);
	}
	
	// ������ AbilityStat�� �ν��Ͻ��� ������Ʈ ����� �ؼ� �ٽ� ������ �����.
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

// ĳ���� �������� �ؾ��Ұ�
void AFPSCPPPlayerController::PawnOnEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	// ĳ���Ͱ� �������� AbilityStat�� ��ȿȭ �ǹǷ� Widget�����Ѵ�.
	if (HUDReference)
	{
		HUDReference->RemoveFromParent();
	}

	/** Actor�� ��������� �ı��� ��� */
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
		if (GameModeBase)
		{
			/** Tries to spawn the player's pawn, at the location returned by FindPlayerStart */
			// void RestartPlayer(AController* NewPlayer);
			// NewPlayer�� �������� ����� ��Ʈ�ѷ�
			GameModeBase->RestartPlayer(this);
		}
	}
}
