// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AliciaPlayerState.h"
#include <AbilitySystems/AliciaAttributeSet.h>
#include <AbilitySystems/AliciaAbilitySystemComponent.h>

AAliciaPlayerState::AAliciaPlayerState()
{
	AbilitySystemCompont = CreateDefaultSubobject<UAliciaAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemCompont->SetIsReplicated(true);
	AbilitySystemCompont->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAliciaAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;


}

UAbilitySystemComponent* AAliciaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemCompont;
}
