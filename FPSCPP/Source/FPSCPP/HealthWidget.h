// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBindInterface.h"
#include "HealthWidget.generated.h"


class UProgressBar;
class UAbilityStatComponent;
/**
 * 
 */
UCLASS()
class FPSCPP_API UHealthWidget : public UUserWidget , public IWidgetBindInterface
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UAbilityStatComponent* AbilityStat;


	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UProgressBar* ProgressBar_Health;

	UFUNCTION()
	void OnChangeHealth(float Prev, float Curr);

	virtual void WidgetBindActor_Implementation(AActor* Source);
	virtual void WidgetBindComponent_Implementation(UActorComponent* Source);
};
