// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityStatComponent.h"

// Sets default values for this component's properties
UAbilityStatComponent::UAbilityStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	DefaultHealth = 100.0f;
}
// Called when the game starts
void UAbilityStatComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	ResetHealth();
	if (Owner)
		Owner->OnTakeAnyDamage.AddDynamic(this,&UAbilityStatComponent::OnTakeAnyDamage);
}
// Called every frame
void UAbilityStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
void UAbilityStatComponent::SetHealth(float Value)
{
	float PrevHealth = Health;
	Health = FMath::Clamp(Value,0.0f, DefaultHealth);
	OnChangeHealth.Broadcast(PrevHealth, Health);
}
void UAbilityStatComponent::TakeDamage(float Value)
{	
	if (Health <= 0.0f || Value <= 0.0f)
		return;
	
	SetHealth(Health - Value);
}

float UAbilityStatComponent::CalculateDamage_Implementation(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	return Damage;
}

void UAbilityStatComponent::AddHealth(float Value)
{
	if (Health <= 0.0f || Value <= 0.0f)
		return;
		
	SetHealth(Health + Value);
}

void UAbilityStatComponent::ResetHealth()
{
	SetHealth(DefaultHealth);
}

void UAbilityStatComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage
, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	float CalcDamage = CalculateDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	TakeDamage(CalcDamage);
}

