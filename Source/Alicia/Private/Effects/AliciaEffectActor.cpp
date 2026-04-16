// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/AliciaEffectActor.h"
#include <Components/SphereComponent.h>
#include <AbilitySystems/AliciaAttributeSet.h>
#include <AbilitySystems/AliciaAbilitySystemComponent.h>
#include <AliciaCharacterBase.h>
#include <AbilitySystemBlueprintLibrary.h>
// Sets default values
AAliciaEffectActor::AAliciaEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* usc = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(usc);


}

// Called when the game starts or when spawned
void AAliciaEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAliciaEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC == nullptr)return;

	check(GameplayEffectClass)
	FGameplayEffectContextHandle contexthandle= TargetASC->MakeEffectContext();
	contexthandle.AddSourceObject(this);
	FGameplayEffectSpecHandle effectspechandle= TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f, contexthandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*effectspechandle.Data.Get());



}

