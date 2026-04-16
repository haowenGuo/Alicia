// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStateComponent.h"
#include <AbilitySystems/AliciaAttributeSet.h>
// Sets default values for this component's properties
UCharacterStateComponent::UCharacterStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UCharacterStateComponent::TakeDamage(float damage)
{

	health -= (damage / defence);
	if (health < 0) {
		health = 0;
	}
	else if (health > maxhealth) {
		health = maxhealth;
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
		FString::Printf(TEXT("health: %.1f,damage: %.1f"),
			health, damage)
	);
	UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
	if (aas) {
		aas->SetHealth(health);
	}
	
	return health;
}

float UCharacterStateComponent::CostStamina(float costvalue)
{
	stamina -= costvalue;
	if (stamina < 0) {
		stamina = 0;
	}
	else if (stamina > maxstamina) {
		stamina = maxstamina;
	}
	UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
	if (aas) {
		aas->SetStamina(stamina);
	}
	
	return stamina;
}

float UCharacterStateComponent::CostMagic(float costvalue)
{
	magic -= costvalue;
	if (magic < 0) {
		magic = 0;
	}
	else if (magic > maxmagic) {
		magic = maxmagic;
	}
	UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
	if (aas) {
		aas->SetMana(magic);
	}
	
	return magic;
}

float UCharacterStateComponent::GetHealthPercent()
{
	if (maxhealth != 0) {
		return health / maxhealth;
	}
	else {
		return 0.f;
	}
}

float UCharacterStateComponent::GetStaminaPercent()
{
	if (maxstamina != 0) {
		return stamina / maxstamina;
	}
	else {
		return 0.f;
	}
}

float UCharacterStateComponent::GetMagicPercent()
{
	if (maxmagic != 0) {
		return magic / maxmagic;
	}
	else {
		return 0.f;
	}
}

void UCharacterStateComponent::InitCsc(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as)
{
	PlayerController= pc;

	PlayerState= ps;

	AbilitySystemComponent= asc;

	AttributeSet= as;

	UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
	if (aas)
	{
		
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetHealthAttribute()).AddUObject(this, &UCharacterStateComponent::HealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxHealthAttribute()).AddUObject(this, &UCharacterStateComponent::MaxHealthChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetStaminaAttribute()).AddUObject(this, &UCharacterStateComponent::StaminaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxStaminaAttribute()).AddUObject(this, &UCharacterStateComponent::MaxStaminaChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetManaAttribute()).AddUObject(this, &UCharacterStateComponent::ManaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxManaAttribute()).AddUObject(this, &UCharacterStateComponent::MaxManaChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetAttackAttribute()).AddUObject(this, &UCharacterStateComponent::AttackChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetDefenceAttribute()).AddUObject(this, &UCharacterStateComponent::DefenceChanged);

		aas->SetHealth(health);
		aas->SetMaxHealth(maxhealth);
		aas->SetStamina(stamina);
		aas->SetMaxStamina(maxstamina);
		aas->SetMana(magic);
		aas->SetMaxMana(maxmagic);
		aas->SetAttack(attack);
		aas->SetDefence(defence);
	}

	/*
	health = aas->GetHealth();
	maxhealth = aas->GetMaxHealth();
	stamina = aas->GetStamina();
	maxstamina = aas->GetMaxStamina();
	magic = aas->GetMana();
	maxmagic = aas->GetMaxMana();
	attack = aas->GetAttack();
	defence = aas->GetDefence();*/
}

void UCharacterStateComponent::InitCsc(UAbilitySystemComponent* asc, UAttributeSet* as)
{
	AbilitySystemComponent = asc;

	AttributeSet = as;

	UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
	if (aas)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetHealthAttribute()).AddUObject(this, &UCharacterStateComponent::HealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxHealthAttribute()).AddUObject(this, &UCharacterStateComponent::MaxHealthChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetStaminaAttribute()).AddUObject(this, &UCharacterStateComponent::StaminaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxStaminaAttribute()).AddUObject(this, &UCharacterStateComponent::MaxStaminaChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetManaAttribute()).AddUObject(this, &UCharacterStateComponent::ManaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetMaxManaAttribute()).AddUObject(this, &UCharacterStateComponent::MaxManaChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetAttackAttribute()).AddUObject(this, &UCharacterStateComponent::AttackChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(aas->GetDefenceAttribute()).AddUObject(this, &UCharacterStateComponent::DefenceChanged);

		aas->SetHealth(health);
		aas->SetMaxHealth(maxhealth);
		aas->SetStamina(stamina);
		aas->SetMaxStamina(maxstamina);
		aas->SetMana(magic);
		aas->SetMaxMana(maxmagic);
		aas->SetAttack(attack);
		aas->SetDefence(defence);
	}

}


void UCharacterStateComponent::HealthChanged(const FOnAttributeChangeData& Data)
{
	float ClampedValue = FMath::Clamp(Data.NewValue, 0.0f, maxhealth);
	if (!FMath::IsNearlyEqual(ClampedValue, Data.NewValue))
	{
		UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
		if (aas)
		{
			aas->SetHealth(ClampedValue);
		}
		
		//SetHealth(ClampedValue);
		// 可选：广播值被修正的事件（用于UI提示等）
		// OnHealthClamped.Broadcast(ClampedValue, Max);
	}
	//health = Data.NewValue;
	health = ClampedValue;
	/*
	if (health > maxhealth)
	{
		health = maxhealth;
		UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
		if (aas) {
			aas->SetHealth(health);
		}
	}*/
};

void UCharacterStateComponent::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	maxhealth = Data.NewValue;
};

void UCharacterStateComponent::StaminaChanged(const FOnAttributeChangeData& Data)
{
	stamina = Data.NewValue;
	/*
	if (stamina > maxstamina)
	{
		stamina = maxstamina;
		UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
		if (aas) {
			aas->SetStamina(stamina);
		}
	}*/
};

void UCharacterStateComponent::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	maxstamina = Data.NewValue;

};

void UCharacterStateComponent::ManaChanged(const FOnAttributeChangeData& Data)
{
	magic = Data.NewValue;
	/*
	if (magic > maxmagic)
	{
		magic = maxmagic;
		UAliciaAttributeSet* aas = Cast<UAliciaAttributeSet>(AttributeSet);
		if (aas) {
			aas->SetMana(magic);
		}
	}*/
};

void UCharacterStateComponent::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	maxmagic = Data.NewValue;

};

void UCharacterStateComponent::AttackChanged(const FOnAttributeChangeData& Data)
{
	attack = Data.NewValue;

};

void UCharacterStateComponent::DefenceChanged(const FOnAttributeChangeData& Data)
{
	defence = Data.NewValue;
};