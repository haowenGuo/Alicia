// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class ALICIA_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Turn(float value);
	void LookUp(float value);
	void MoveForward(float value);
	void MoveRight(float value);


	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* collsion;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* skeletalmesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springarm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
