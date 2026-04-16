// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include <Weapons/Sword.h>
#include <MyActor.h>
#include"CharacterStateComponent.h"
#include "Components/WidgetComponent.h"
#include <Widges/EnemyWidget.h>
#include <Kismet/GameplayStatics.h>
#include <NiagaraFunctionLibrary.h>
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	//GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springarm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	spherecollision = CreateDefaultSubobject<USphereComponent>(TEXT("spherecollision"));
	springarm->SetupAttachment(GetRootComponent());
	spherecollision->SetupAttachment(GetRootComponent());
	camera->SetupAttachment(springarm);
	csc = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("characterstatecomponent"));
	widgecomponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("widgecomponent"));
	widgecomponent->SetupAttachment(GetRootComponent());
	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	spherecollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnBeginOverlap);
	spherecollision->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnEndOverlap);
	uw = Cast<UEnemyWidget>(widgecomponent->GetUserWidgetObject());
	if (uw) {
		uw->AddToViewport();
		widgecomponent->SetVisibility(false);
	}
}
void AMyCharacter::Turn(float value)
{
	if (Controller && (value != 0.f))
	{
		AddControllerYawInput(value);
	}
}

void AMyCharacter::LookUp(float value)
{
	if (Controller && (value != 0.f))
	{
		AddControllerPitchInput(value);
	}
}

void AMyCharacter::MoveForward(float value)
{
	FVector location = GetActorLocation();
	if (Controller && (value != 0.f))
	{
		if (characterstate_montage == ECharacterState_montage::ECS_Idle)
		{
			const FRotator ControlRoattion = GetControlRotation();
			const FRotator YawRotation(0.f, ControlRoattion.Yaw, 0.f);
			FVector forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(forward, value);
		}
	}
}

void AMyCharacter::MoveRight(float value)
{
	if (Controller && (value != 0.f))
	{
		if (characterstate_montage == ECharacterState_montage::ECS_Idle)
		{
			const FRotator ControlRoattion = GetControlRotation();
			const FRotator YawRotation(0.f, ControlRoattion.Yaw, 0.f);
			FVector right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(right, value);
		}
	}
}
void AMyCharacter::MyJump()
{
	if (jumping==false) {
		if (characterstate_montage == ECharacterState_montage::ECS_Idle)
		{
			Jump();
		}
	}
}
void AMyCharacter::PressE()
{

	ASword *sword0=Cast<ASword>(pickup_item);
	if (sword0) {
		if (sword) {
			FString s0 = FString("change sword") ;
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
			}
			sword->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		}
		/*
		FString s0 = FString("get sword0:") + sword0->GetName();
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
		}*/
		FAttachmentTransformRules rule(EAttachmentRule::SnapToTarget, true);
		//sword0->staticmesh->AttachToComponent(this->GetMesh(), rule, FName("RightHandSword"));
		sword0->AttachToComponent(this->GetMesh(), rule, FName("RightHandSword"));
		characterstate = ECharacterState::ECS_ArmedSword;
		//sword0->SetSwordOwner(this);
		sword = sword0;
		
	}
}
void AMyCharacter::PressMouse0()
{
	UAnimInstance* instance = GetMesh()->GetAnimInstance();
	if (instance && montage && characterstate == ECharacterState::ECS_ArmedSword ) {
		if (characterstate_montage == ECharacterState_montage::ECS_Idle)
		{
			instance->Montage_Play(montage);
			instance->Montage_JumpToSection(FName("Attack0"));
			characterstate_montage = ECharacterState_montage::ECS_Playing;
		}
		else if (characterstate_montage == ECharacterState_montage::ECS_Attack0)
		{
			instance->Montage_Play(montage);
			instance->Montage_JumpToSection(FName("Attack1"));
			characterstate_montage = ECharacterState_montage::ECS_Playing;
		}
		else if (characterstate_montage == ECharacterState_montage::ECS_Attack1)
		{
			instance->Montage_Play(montage);
			instance->Montage_JumpToSection(FName("Attack2"));
			characterstate_montage = ECharacterState_montage::ECS_Playing;
		}

	}
}
void AMyCharacter::PressMouse1()
{

	UAnimInstance* instance = GetMesh()->GetAnimInstance();
	if (instance && montage && characterstate==ECharacterState::ECS_ArmedSword && characterstate_montage == ECharacterState_montage::ECS_Idle) {
		FString s0 = FString("Defend ");
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
		}
		instance->Montage_Play(montage);
		instance->Montage_JumpToSection(FName("Defend"));
		characterstate_montage = ECharacterState_montage::ECS_Playing;
	}
}
void AMyCharacter::RealeaseMouse1()
{
	UAnimInstance* instance = GetMesh()->GetAnimInstance();
	if (instance && montage && characterstate == ECharacterState::ECS_ArmedSword ) {
		if (instance->Montage_IsPlaying(montage))
		{
			FString s0 = FString("Defend realease");
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
			}
			//instance->Montage_Stop(0.1f,montage);
			
			// 获取当前蒙太奇播放的片段名称
			FName CurrentSection = instance->Montage_GetCurrentSection(montage);

			// 检查是否是目标片段
			if (CurrentSection == FName("Defend"))
			{
				instance->Montage_Stop(0.1f, montage);
			}
		}

		characterstate_montage = ECharacterState_montage::ECS_Idle;
	}
}
void AMyCharacter::PressKey1()
{

	if (sword && characterstate == ECharacterState::ECS_ArmedSword) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("press1"));
		}
		UAnimInstance* instance = GetMesh()->GetAnimInstance();
		if (instance && equip_montage && characterstate_montage == ECharacterState_montage::ECS_Idle) {

			instance->Montage_Play(equip_montage);
			instance->Montage_JumpToSection(FName("DisEquip"));
			characterstate_montage = ECharacterState_montage::ECS_Playing;		
		}
	}
	else if (sword && characterstate != ECharacterState::ECS_ArmedSword) {
		UAnimInstance* instance = GetMesh()->GetAnimInstance();
		if (instance && equip_montage && characterstate_montage == ECharacterState_montage::ECS_Idle) {

			instance->Montage_Play(equip_montage);
			instance->Montage_JumpToSection(FName("Equip"));
			characterstate_montage = ECharacterState_montage::ECS_Playing;		
			//FAttachmentTransformRules rule(EAttachmentRule::SnapToTarget, true);
			//sword->staticmesh->AttachToComponent(this->GetMesh(), rule, FName("RightHandSword"));
			//characterstate = ECharacterState::ECS_ArmedSword;
		}
	}
}

void AMyCharacter::DisEquip()
{
	if (sword) {
		FAttachmentTransformRules rule(EAttachmentRule::SnapToTarget, true);
		sword->staticmesh->AttachToComponent(this->GetMesh(), rule, FName("Equipment_sword"));
		characterstate = ECharacterState::ECS_UNARMED;
	}

}

int AMyCharacter::GetHit(FVector impactpoint, AActor* attackactor, float damage)
{
	FVector forward = GetActorForwardVector();
	FVector hitdir = (attackactor->GetActorLocation() - GetActorLocation());
	hitdir.Z = 0;
	hitdir.Normalize();
	float cosdelta = forward.Dot(hitdir);
	float dir = forward.Cross(hitdir).Z;
	if (characterstate_montage == ECharacterState_montage::ECS_StartDefend ) {
		if (cosdelta > 0) {
			return 2;
		}
		
	}
	else if (characterstate_montage == ECharacterState_montage::ECS_Defend)
	{
		if (cosdelta > 0 && damage<1.f) {
			return 1;
		}
		
	}
	UAnimInstance* anim = GetMesh()->GetAnimInstance();


	if (anim && hitmontage) {
		FName direction("From_Back");
		if (cosdelta <= 1.f && cosdelta > 0.7f) {
			direction = FName("From_Front");
		}
		else if (cosdelta >= -0.7f) {
			if (dir > 0)
			{
				direction = FName("From_Right");
			}
			else {
				direction = FName("From_Left");
			}

		}
		characterstate_montage = ECharacterState_montage::ECS_Playing;
		anim->Montage_Play(hitmontage);
		anim->Montage_JumpToSection(direction);
		//anim->Montage_JumpToSection(FName("From_Front"));
	}
	if (hitsound) {
		UGameplayStatics::PlaySoundAtLocation(this, hitsound, impactpoint);
	}
	if (hitparticle) {
		UGameplayStatics::SpawnEmitterAtLocation(this, hitparticle, impactpoint);
	}
	if (hitparticle2) {
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			hitparticle2,
			impactpoint
		);
	}
	
	if (csc) {
		if (characterstate_montage == ECharacterState_montage::ECS_Defend) {
			damage = damage * 0.8;
		}
		csc->TakeDamage(damage);
	}
	if (uw && csc) {

		uw->SetHealth(csc->GetHealthPercent());
		if (csc->health <= 0) {
			characterstate_montage = ECharacterState_montage::ECS_Playing;
			uw->RemoveFromParent();
			if (hitmontage)
			{
				anim->Montage_Play(deathmontage);
				anim->Montage_JumpToSection(FName("Death"));
				TArray<UActorComponent*> Components;
				GetComponents(Components);

				for (UActorComponent* Component : Components)
				{
					if (UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Component))
					{
						// 禁用碰撞
						Primitive->SetCollisionEnabled(ECollisionEnabled::NoCollision);

						// 可选：设置为忽略所有通道
						Primitive->SetCollisionResponseToAllChannels(ECR_Ignore);
					}
				}
			}

			//anim->Montage_JumpToSection(direction);
		}
	}

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("get hit"));
	}
	return 1;
}

void AMyCharacter::PressKeyG()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("pressG"));
	}
	if (sword && characterstate==ECharacterState::ECS_ArmedSword) {
		sword->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		sword = nullptr;
	}
	if (bow && characterstate == ECharacterState::ECS_ArmedBow) {
		bow = nullptr;
	}
}
void AMyCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	FString s = OtherActor->GetName();
	FString s0 = FString("begin overlap:")+s;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
	}
	*/
}
void AMyCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*
	FString s = OtherActor->GetName();
	FString s0 = FString("end overlap:") + s;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
	}*/
}
// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector location = GetActorLocation();
	//DrawDebugLine(GetWorld(), location, location + FVector(0.f, 0.f, 100.f), FColor::Blue, false, -1, 0, 2.0f);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed,this, &AMyCharacter::MyJump);
	PlayerInputComponent->BindAction(FName("keye"), IE_Pressed, this, &AMyCharacter::PressE);
	PlayerInputComponent->BindAction(FName("Attack0"), IE_Pressed, this, &AMyCharacter::PressMouse0);
	PlayerInputComponent->BindAction(FName("Attack1"), IE_Pressed, this, &AMyCharacter::PressMouse1);
	PlayerInputComponent->BindAction(FName("Attack1"), IE_Released, this, &AMyCharacter::RealeaseMouse1);
	PlayerInputComponent->BindAction(FName("key1"), IE_Pressed, this, &AMyCharacter::PressKey1);
	PlayerInputComponent->BindAction(FName("keyg"), IE_Pressed, this, &AMyCharacter::PressKeyG);
}

UCharacterStateComponent* AMyCharacter::GetCsc()
{
	return csc;
}



