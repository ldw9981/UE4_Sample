// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "Components/ProgressBar.h"
#include "AbilityStatComponent.h"


void UHealthWidget::OnChangeHealth(float Prev, float Curr)
{
	ProgressBar_Health->SetPercent(AbilityStat->GetPercentHealth());
}

void UHealthWidget::Bind(UAbilityStatComponent* Source)
{
	AbilityStat = Source;
	AbilityStat->OnChangeHealth.AddDynamic(this, &UHealthWidget::OnChangeHealth);	
	ProgressBar_Health->SetPercent(AbilityStat->GetPercentHealth());
}
