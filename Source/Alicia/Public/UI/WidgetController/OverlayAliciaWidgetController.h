// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AliciaWidgetController.h"
#include <GameplayEffectTypes.h>
#include "OverlayAliciaWidgetController.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float, NewStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChangedSignature, float, NewMaxStamina);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackChangedSignature, float, NewAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDefenceChangedSignature, float, NewDefence);

UCLASS(BlueprintType,Blueprintable)
class ALICIA_API UOverlayAliciaWidgetController : public UAliciaWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValues()override;

	virtual void BindCallbacksToDependencies()override;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnStaminaChangedSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnMaxStaminaChangedSignature OnMaxStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnMaxManaChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnAttackChangedSignature OnAttackChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS")
	FOnDefenceChangedSignature OnDefenceChanged;

protected:
	void HealthChanged(const FOnAttributeChangeData& Data)const;

	void MaxHealthChanged(const FOnAttributeChangeData& Data)const;

	void StaminaChanged(const FOnAttributeChangeData& Data)const;

	void MaxStaminaChanged(const FOnAttributeChangeData& Data)const;

	void ManaChanged(const FOnAttributeChangeData& Data)const;

	void MaxManaChanged(const FOnAttributeChangeData& Data)const;

	void AttackChanged(const FOnAttributeChangeData& Data)const;

	void DefenceChanged(const FOnAttributeChangeData& Data)const;
};
