// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	skeletalmesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("skletalmesh"));
	collsion = CreateDefaultSubobject<UCapsuleComponent>(TEXT("collsion"));
	springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springarm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	collsion->SetCapsuleHalfHeight(180.f);
	collsion->SetCapsuleRadius(60.f);
	SetRootComponent(collsion);
	skeletalmesh->SetupAttachment(GetRootComponent());
	springarm->SetupAttachment(GetRootComponent());
	camera->SetupAttachment(springarm);
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABird::Turn(float value)
{
	if (Controller && (value != 0.f))
	{
		AddControllerYawInput(value);
	}
}

void ABird::LookUp(float value)
{
	if (Controller && (value != 0.f))
	{
		AddControllerPitchInput(value);
	}
}

void ABird::MoveForward(float value)
{
	FVector location = GetActorLocation();
	if (Controller && (value != 0.f))
	{
		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, value);
	}
}

void ABird::MoveRight(float value)
{
	if (Controller && (value != 0.f))
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, value);
	}
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABird::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABird::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABird::LookUp);
}

