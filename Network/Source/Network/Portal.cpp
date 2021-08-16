// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Network.h"
#include "Engine/AssetManager.h"



APortal::APortal()
{
	this->OnActorBeginOverlap.AddDynamic(this, &APortal::BeginOverlap);
}

void APortal::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (GetWorld()->GetNetMode() != NM_DedicatedServer)
		return;

	if (HasAuthority() == false)
		return;

	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn == nullptr)
		return;

	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (PlayerController == nullptr)
		return;

	if (PortalIndex == 0)
		return;

	FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
	const FSoftObjectPath& AssetRef = PortalDataTableSOPtr.ToSoftObjectPath();

	
	StreamableManager.RequestSyncLoad(AssetRef);
	UDataTable* DataTable = Cast< UDataTable >(PortalDataTableSOPtr.Get());
	if (DataTable == nullptr)
		return;

	FPortalInfo* Portal = DataTable->FindRow<FPortalInfo>(*FString::FromInt(PortalIndex), TEXT("Name"));
	if (Portal == nullptr)
		return;

	UE_LOG(LogNetwork, Log, TEXT("ClientTravel %s %d %d"), *Portal->TravelURL , int(Portal->TravelType), Portal->bSeamless);

	PlayerController->ClientTravel(Portal->TravelURL, Portal->TravelType, Portal->bSeamless);
	StreamableManager.Unload(AssetRef);
}