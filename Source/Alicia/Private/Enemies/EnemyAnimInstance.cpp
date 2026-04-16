// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAnimInstance.h"
#include "Enemies/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	enemy = Cast<AEnemy>(TryGetPawnOwner());
	if (enemy) {
		movementcomponent = enemy->GetCharacterMovement();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float Deltatime)
{
	Super::NativeUpdateAnimation(Deltatime);
	if (enemy) {
		goundspeed = UKismetMathLibrary::VSize(movementcomponent->Velocity);
		isfall = movementcomponent->IsFalling();

	}
}