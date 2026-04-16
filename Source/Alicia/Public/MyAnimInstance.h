// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include"CharacterState.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ALICIA_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation()override;
	virtual void NativeUpdateAnimation(float Deltatime)override;
protected:
	UPROPERTY(BlueprintReadOnly)
	class AMyCharacter* mycharacter;

	UPROPERTY(BlueprintReadOnly)
	class UCharacterMovementComponent* movementcomponent;

	UPROPERTY(BlueprintReadOnly)
	float goundspeed;

	UPROPERTY(BlueprintReadOnly)
	bool isfall;

	UPROPERTY(BlueprintReadWrite)
	bool isjumping;

	UPROPERTY(BlueprintReadWrite)
	ECharacterState characterstate;
};
