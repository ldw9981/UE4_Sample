// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "Components/ProgressBar.h"
#include "AbilityStatComponent.h"


void UHealthWidget::OnChangeHealth(float Prev, float Curr)
{
	if (Curr > 0.0f)
	{
		ProgressBar_Health->SetPercent(AbilityStat->GetPercentHealth());
	}
	else
	{
		ProgressBar_Health->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UHealthWidget::Bind(UAbilityStatComponent* Source)
{
	if (Source!=nullptr)
	{
		AbilityStat = Source;
		AbilityStat->OnChangeHealth.AddDynamic(this, &UHealthWidget::OnChangeHealth);
	}
	
}
