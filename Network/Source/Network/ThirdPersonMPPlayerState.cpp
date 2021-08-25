// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonMPPlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

AThirdPersonMPPlayerState::AThirdPersonMPPlayerState()
{
	Kill = 0;
	Death = 0;
}

void AThirdPersonMPPlayerState::OnRep_KDA()
{
	FString Message = FString::Printf(TEXT("%s OnRep_KDA %d %d"),*this->GetName(), Kill, Death);

	UKismetSystemLibrary::PrintString(GetWorld(), Message);
}
void AThirdPersonMPPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AThirdPersonMPPlayerState, Kill);
	DOREPLIFETIME(AThirdPersonMPPlayerState, Death);
}