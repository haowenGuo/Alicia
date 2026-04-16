// Fill out your copyright notice in the Description page of Project Settings.


#include "AliciaCharacterBase.h"

// Sets default values
AAliciaCharacterBase::AAliciaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* AAliciaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemCompont;
}

// Called when the game starts or when spawned
void AAliciaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAliciaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAliciaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

