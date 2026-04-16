// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameplayEffectTypes.h>
#include "CharacterStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALICIA_API UCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float TakeDamage(float damage);
	float CostStamina(float costvalue);
	float CostMagic(float costvalue);
	float GetHealthPercent();
	float GetStaminaPercent();
	float GetMagicPercent();
	void InitCsc(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as);

	void InitCsc(UAbilitySystemComponent* asc, UAttributeSet* as);
	UPROPERTY(EditAnywhere)
	float health=100;
	UPROPERTY(EditAnywhere)
	float maxhealth = 100;
	UPROPERTY(EditAnywhere)
	float stamina = 100;
	UPROPERTY(EditAnywhere)
	float maxstamina = 100;
	UPROPERTY(EditAnywhere)
	float magic = 100;
	UPROPERTY(EditAnywhere)
	float maxmagic = 100;
	UPROPERTY(EditAnywhere)
	float attack = 1;
	UPROPERTY(EditAnywhere)
	float defence = 1;
	UPROPERTY(EditAnywhere)
	float magic_strength = 1;

	void HealthChanged(const FOnAttributeChangeData& Data);

	void MaxHealthChanged(const FOnAttributeChangeData& Data);

	void StaminaChanged(const FOnAttributeChangeData& Data);

	void MaxStaminaChanged(const FOnAttributeChangeData& Data);

	void ManaChanged(const FOnAttributeChangeData& Data);

	void MaxManaChanged(const FOnAttributeChangeData& Data);

	void AttackChanged(const FOnAttributeChangeData& Data);

	void DefenceChanged(const FOnAttributeChangeData& Data);

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
