// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "Components/ProgressBar.h"
#include "AbilityStatComponent.h"


void UHealthWidget::OnChangeHealth(float Prev, float Curr ,float Percent)
{
	ProgressBar_Health->SetPercent(Percent);
}

void UHealthWidget::BindSource_Implementation(AActor* Source)
{
	if (Source!=nullptr)
	{
		AbilityStat = Cast<UAbilityStatComponent>(Source->GetComponentByClass(UAbilityStatComponent::StaticClass()));
		AbilityStat->OnChangeHealth.AddDynamic(this, &UHealthWidget::OnChangeHealth);
		ProgressBar_Health->SetPercent(AbilityStat->GetPercentHealth());
	}
	
}
