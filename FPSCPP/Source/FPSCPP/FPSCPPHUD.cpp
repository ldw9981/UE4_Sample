// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCPPHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AFPSCPPHUD::AFPSCPPHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void AFPSCPPHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void AFPSCPPHUD::BeginPlay()
{
	Super::BeginPlay();
		
	if (UKismetSystemLibrary::IsValidClass(HUDWidgetClass))
	{
		HUDWidgetRef = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(),0), HUDWidgetClass);
		if (HUDWidgetRef != nullptr)
		{			
			HUDWidgetRef->AddToViewport();
		}
	}
}

void AFPSCPPHUD::WidgetBindComponent_Implementation(UActorComponent* Source)
{

}

void AFPSCPPHUD::WidgetBindActor_Implementation(AActor* Source)
{
	if (HUDWidgetRef != nullptr)
	{
		UObject* Object = Cast<UObject>(HUDWidgetRef);
		if (Object)
		{
			IWidgetBindInterface::Execute_WidgetBindActor(Object, Source);
		}
	}
}
