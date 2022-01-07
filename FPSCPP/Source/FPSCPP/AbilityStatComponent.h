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
	// UPROPERTY(VisibleAnywhere) 속성창 보기만 가능
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = AbilityStat)
	float Health;

	// UPROPERTY(EditAnywhere) 인스턴스,블루프린트 편집가능
	UPROPERTY(EditAnywhere, Category = AbilityStat) 
	float DefaultHealth;

	// BlueprintAssignable 이벤트 디스패처 구현
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

	//UFUNCTION(BlueprintCallable) 블루프린트에서 호출 가능
	UFUNCTION(BlueprintCallable)
	void SetHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Value);

	// 상속받은 BP에서 데미지 함수를 재정의 할수있도록 한다.
	UFUNCTION(BlueprintNativeEvent)
	float CalculateDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType , class AController* InstigatedBy, AActor* DamageCauser);
	float CalculateDamage_Implementation(AActor* DamagedActor, float Damage, const class UDamageType* DamageType , class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void AddHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void ResetHealth();

	

	UFUNCTION()			// 함수 등록을 위한 키워드 사용
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType
	, class AController* InstigatedBy, AActor* DamageCauser);
};
