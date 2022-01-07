// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeHealthSignature, float, Prev, float, Curr);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSCPP_API UAbilityStatComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// UPROPERTY(VisibleAnywhere) �Ӽ�â ���⸸ ����
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = AbilityStat)
	float Health;

	// UPROPERTY(EditAnywhere) �ν��Ͻ�,�������Ʈ ��������
	UPROPERTY(EditAnywhere, Category = AbilityStat) 
	float DefaultHealth;

	// BlueprintAssignable �̺�Ʈ ����ó ����
	UPROPERTY(VisibleAnywhere,BlueprintAssignable, Category = AbilityStat)
	FOnChangeHealthSignature	OnChangeHealth;
public:	
	// Sets default values for this component's properties
	UAbilityStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UFUNCTION(BlueprintCallable) �������Ʈ���� ȣ�� ����
	UFUNCTION(BlueprintCallable)
	void SetHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Value);

	// ��ӹ��� BP���� ������ �Լ��� ������ �Ҽ��ֵ��� �Ѵ�.
	UFUNCTION(BlueprintNativeEvent)
	float CalculateDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType , class AController* InstigatedBy, AActor* DamageCauser);
	float CalculateDamage_Implementation(AActor* DamagedActor, float Damage, const class UDamageType* DamageType , class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void AddHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void ResetHealth();

	

	UFUNCTION()			// �Լ� ����� ���� Ű���� ���
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType
	, class AController* InstigatedBy, AActor* DamageCauser);
};
