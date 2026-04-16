// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystems/AliciaAttributeSet.h"
#include <AbilitySystems/AliciaAbilitySystemComponent.h>
#include <Net/UnrealNetwork.h>
UAliciaAttributeSet::UAliciaAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);

	InitStamina(100.f);
	InitMaxStamina(100.f);

	InitMana(100.f);
	InitMaxMana(100.f);

	InitAttack(10.f);
	InitDefence(10.f);
}

void UAliciaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAliciaAttributeSet, Health, COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAliciaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAliciaAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAliciaAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAliciaAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAliciaAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAliciaAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAliciaAttributeSet, Defence, COND_None, REPNOTIFY_Always);
}

void UAliciaAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);
    
    // 1. 处理当前生命值：限制在 [0, MaxHealth] 范围内
    if (Attribute == GetHealthAttribute())
    {
        // 获取当前最大生命值作为上限
        float Max = GetMaxHealth();

        // 限制最小值为0，最大值为MaxHealth
        float ClampedValue = FMath::Clamp(NewValue, 0.0f, Max);

        // 若修正后的值与原值不同，更新属性（避免无意义的重复设置）
        if (!FMath::IsNearlyEqual(ClampedValue, NewValue))
        {
            SetHealth(ClampedValue);
            // 可选：广播值被修正的事件（用于UI提示等）
            // OnHealthClamped.Broadcast(ClampedValue, Max);
        }
    }
    // 2. 处理当前魔法值：限制在 [0, MaxMana] 范围内
    else if (Attribute == GetManaAttribute())
    {
        float Max = GetMaxMana();
        float ClampedValue = FMath::Clamp(NewValue, 0.0f, Max);

        if (!FMath::IsNearlyEqual(ClampedValue, NewValue))
        {
            SetMana(ClampedValue);
        }
    }
    // 2. 处理STAMINA：限制在 [0, MaxMana] 范围内
    else if (Attribute == GetStaminaAttribute())
    {
        float Max = GetMaxStamina();
        float ClampedValue = FMath::Clamp(NewValue, 0.0f, Max);

        if (!FMath::IsNearlyEqual(ClampedValue, NewValue))
        {
            SetMana(ClampedValue);
        }
    }
    // 3. 处理最大生命值变化：若当前生命值超过新的最大值，同步修正
    else if (Attribute == GetMaxHealthAttribute())
    {
        // 新的最大值不能小于0（额外保护）
        float ClampedMax = FMath::Max(NewValue, 0.0f);
        if (!FMath::IsNearlyEqual(ClampedMax, NewValue))
        {
            SetMaxHealth(ClampedMax);
        }

        // 确保当前生命值不超过新的最大值
        float Current = GetHealth();
        if (Current > ClampedMax)
        {
            SetHealth(ClampedMax);
        }
    }
    // 4. 处理最大魔法值变化：同理修正当前魔法值
    else if (Attribute == GetMaxManaAttribute())
    {
        float ClampedMax = FMath::Max(NewValue, 0.0f);
        if (!FMath::IsNearlyEqual(ClampedMax, NewValue))
        {
            SetMaxMana(ClampedMax);
        }

        float Current = GetMana();
        if (Current > ClampedMax)
        {
            SetMana(ClampedMax);
        }
    }
    // 6. 处理最大耐力值变化：同理修正当前耐力值
    else if (Attribute == GetMaxStaminaAttribute())
    {
        float ClampedMax = FMath::Max(NewValue, 0.0f);
        if (!FMath::IsNearlyEqual(ClampedMax, NewValue))
        {
            SetMaxStamina(ClampedMax);
        }

        float Current = GetStamina();
        if (Current > ClampedMax)
        {
            SetStamina(ClampedMax);
        }
    }
}

void UAliciaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAliciaAttributeSet, Health, OldHealth);
}

void UAliciaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAliciaAttributeSet, MaxHealth, OldMaxHealth);
}

void UAliciaAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAliciaAttributeSet, Stamina, OldStamina);
}

void UAliciaAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAliciaAttributeSet, MaxStamina, OldMaxStamina);
}

void UAliciaAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAliciaAttributeSet, Mana, OldMana);
}

void UAliciaAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAliciaAttributeSet, MaxMana, OldMaxMana);
}

void UAliciaAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAliciaAttributeSet, Attack, OldAttack);
}

void UAliciaAttributeSet::OnRep_Defence(const FGameplayAttributeData& OldDefence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAliciaAttributeSet, Defence, OldDefence);
}
