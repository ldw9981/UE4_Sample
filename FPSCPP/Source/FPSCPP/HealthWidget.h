// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"


class UProgressBar;
class UAbilityStatComponent;
/**
 * 
 */
UCLASS()
class FPSCPP_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UAbilityStatComponent* AbilityStat;


	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar_Health;

	UFUNCTION()
	void OnChangeHealth(float Prev, float Curr);

	UFUNCTION(BlueprintCallable)
	void Bind(UAbilityStatComponent* Source);
};
