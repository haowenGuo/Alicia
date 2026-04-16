// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayAliciaWidgetController.h"
#include <AbilitySystems/AliciaAttributeSet.h>

void UOverlayAliciaWidgetController::BroadcastInitialValues()
{
	UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
	if (aas) {
		OnHealthChanged.Broadcast(aas->GetHealth());
		OnMaxHealthChanged.Broadcast(aas->GetMaxHealth());
		OnStaminaChanged.Broadcast(aas->GetStamina());
		OnMaxStaminaChanged.Broadcast(aas->GetMaxStamina());
		OnManaChanged.Broadcast(aas->GetMana());
		OnMaxManaChanged.Broadcast(aas->GetMaxMana());
		OnAttackChanged.Broadcast(aas->GetAttack());
		OnDefenceChanged.Broadcast(aas->GetDefence());
	}
	BindCallbacksToDependencies();
}

void UOverlayAliciaWidgetController::BindCallbacksToDependencies()
{
	UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetHealthAttribute()).AddUObject(this, &UOverlayAliciaWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxHealthAttribute()).AddUObject(this, &UOverlayAliciaWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetStaminaAttribute()).AddUObject(this, &UOverlayAliciaWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxStaminaAttribute()).AddUObject(this, &UOverlayAliciaWidgetController::MaxStaminaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetManaAttribute()).AddUObject(this, &UOverlayAliciaWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxManaAttribute()).AddUObject(this, &UOverlayAliciaWidgetController::MaxManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetAttackAttribute()).AddUObject(this, &UOverlayAliciaWidgetController::AttackChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetDefenceAttribute()).AddUObject(this, &UOverlayAliciaWidgetController::DefenceChanged);
}

void UOverlayAliciaWidgetController::HealthChanged(const FOnAttributeChangeData& Data)const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayAliciaWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayAliciaWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UOverlayAliciaWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}

void UOverlayAliciaWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayAliciaWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void UOverlayAliciaWidgetController::AttackChanged(const FOnAttributeChangeData& Data) const
{
	OnAttackChanged.Broadcast(Data.NewValue);
}

void UOverlayAliciaWidgetController::DefenceChanged(const FOnAttributeChangeData& Data) const
{
	OnDefenceChanged.Broadcast(Data.NewValue);
}
