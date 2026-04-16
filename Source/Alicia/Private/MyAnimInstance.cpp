// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	mycharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	if (mycharacter) {
		movementcomponent = mycharacter->GetCharacterMovement();
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float Deltatime)
{
	Super::NativeUpdateAnimation(Deltatime);
	if (mycharacter) {
		goundspeed = UKismetMathLibrary::VSize(movementcomponent->Velocity);
		isfall = movementcomponent->IsFalling();
		mycharacter->jumping = isjumping;
		characterstate=mycharacter->characterstate;
	}
}
