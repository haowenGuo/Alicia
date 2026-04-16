// Copyright Epic Games, Inc. All Rights Reserved.

#include "AliciaCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Animation/AnimMontage.h"
#include <Weapons/Sword.h>
#include <MyActor.h>
#include"CharacterStateComponent.h"
#include "Components/WidgetComponent.h"
#include <Widges/EnemyWidget.h>
#include <Kismet/GameplayStatics.h>
#include <NiagaraFunctionLibrary.h>
#include <Player/AliciaPlayerState.h>

#include <AbilitySystems/AliciaAbilitySystemComponent.h>
#include <Player/AliciaPlayerController.h>
#include <UI/AliciaHUD.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AAliciaCharacter

AAliciaCharacter::AAliciaCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	spherecollision = CreateDefaultSubobject<USphereComponent>(TEXT("spherecollision"));
	spherecollision->SetupAttachment(GetRootComponent());
	csc = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("characterstatecomponent"));
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AAliciaCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (spherecollision) {
		spherecollision->OnComponentBeginOverlap.AddDynamic(this, &AAliciaCharacter::OnBeginOverlap);
		spherecollision->OnComponentEndOverlap.AddDynamic(this, &AAliciaCharacter::OnEndOverlap);
	}

}

void AAliciaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AAliciaPlayerState* APS=GetPlayerState<AAliciaPlayerState>();
	check(APS);
	APS->GetAbilitySystemComponent()->InitAbilityActorInfo(APS,this);
	AbilitySystemCompont = APS->GetAbilitySystemComponent();
	AttributeSet = APS->GetAttributeSet();


	if (AAliciaPlayerController* apc = Cast<AAliciaPlayerController>(GetController()))
	{
		if (csc)
		{
			csc->InitCsc(apc, APS, AbilitySystemCompont, AttributeSet);
		}
		AAliciaHUD* ah=Cast<AAliciaHUD>(apc->GetHUD());
		if (ah) {
			ah->InitOverlay(apc, APS, AbilitySystemCompont, AttributeSet);
		}
	}
}

void AAliciaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AAliciaPlayerState* APS = GetPlayerState<AAliciaPlayerState>();
	check(APS);
	APS->GetAbilitySystemComponent()->InitAbilityActorInfo(APS, this);
	AbilitySystemCompont = APS->GetAbilitySystemComponent();
	AttributeSet = APS->GetAttributeSet();
	
	if (AAliciaPlayerController* apc = Cast<AAliciaPlayerController>(GetController()))
	{
		AAliciaHUD* ah = Cast<AAliciaHUD>(apc->GetHUD());
		if (ah) {
			ah->InitOverlay(apc, APS, AbilitySystemCompont, AttributeSet);
		}
	}
}

int32 AAliciaCharacter::EquipRightWeapon(AActor* equipment)
{
	ASword* sword0 = Cast<ASword>(equipment);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("EquipRightWeapon"));
	}
	if (sword0) {
		
		if (sword) {
			UnEquipRightWeapon();
			/*
			FString s0 = FString("change sword");
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
			}

			sword->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			sword->Destroy();*/
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
		sword0->SetSwordOwner(this);
		
		sword = sword0;
		return 1;
	}
	return 0;
}

int32 AAliciaCharacter::EquipLeftWeapon(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::EquipUpperBody(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::EquipLowerBody(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::EquipHead(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::EquipHand(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::EquipArm(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::EquipFoot(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::EquipRing(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::EquipNeck(AActor* equipment)
{
	return 0;
}

int32 AAliciaCharacter::UnEquipRightWeapon()
{
	if (!sword)return 0;
	ASword* sw = Cast<ASword>(sword);
	if (sw)
	{
		sw->RemoveEffect();
	}
	if (sword) {
		
		sword->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		sword->Destroy();
		characterstate = ECharacterState::ECS_UNARMED;
	}
	return 1;
}

int32 AAliciaCharacter::UnEquipLeftWeapon()
{
	return 0;
}

int32 AAliciaCharacter::UnEquipUpperBody()
{
	return 0;
}

int32 AAliciaCharacter::UnEquipLowerBody()
{
	return 0;
}

int32 AAliciaCharacter::UnEquipHead()
{
	return 0;
}

int32 AAliciaCharacter::UnEquipHand()
{
	return 0;
}

int32 AAliciaCharacter::UnEquipArm()
{
	return 0;
}

int32 AAliciaCharacter::UnEquipFoot()
{
	return 0;
}

int32 AAliciaCharacter::UnEquipRing()
{
	return 0;
}

int32 AAliciaCharacter::UnEquipNeck()
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAliciaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAliciaCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AAliciaCharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAliciaCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAliciaCharacter::Look);

		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressMouse0);

		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AAliciaCharacter::RealeaseMouse0);

		// Defend
		EnhancedInputComponent->BindAction(DefendAction, ETriggerEvent::Completed, this, &AAliciaCharacter::RealeaseMouse1);

		// Defend
		EnhancedInputComponent->BindAction(DefendAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressMouse1);

		// E
		EnhancedInputComponent->BindAction(EAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressE);

		// G
		EnhancedInputComponent->BindAction(GAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressKeyG);

		// Q
		EnhancedInputComponent->BindAction(QAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressKeyQ);

		// R
		EnhancedInputComponent->BindAction(RAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressKeyR);

		// M
		EnhancedInputComponent->BindAction(MAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressKeyM);

		// P
		EnhancedInputComponent->BindAction(PAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressKeyP);

		// ESC
		EnhancedInputComponent->BindAction(ESCAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressKeyEsc);

		// TAB
		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Started, this, &AAliciaCharacter::PressKeyTab);

		// TAB
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &AAliciaCharacter::Roll);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AAliciaCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (characterstate_montage != ECharacterState_montage::ECS_Idle) { return; }

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAliciaCharacter::Jump()
{
	if (characterstate_montage != ECharacterState_montage::ECS_Idle) { return; }
	Super::Jump();
}

void AAliciaCharacter::StopJumping()
{
	if (characterstate_montage != ECharacterState_montage::ECS_Idle) { return; }
	Super::StopJumping();
}

void AAliciaCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAliciaCharacter::PressE()
{

	ASword* sword0 = Cast<ASword>(pickup_item);
	if (sword0) {
		if (sword) {
			FString s0 = FString("change sword");
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
		sword0->SetSwordOwner(this);
		sword = sword0;

	}
}
void AAliciaCharacter::PressMouse0()
{
	UAnimInstance* instance = GetMesh()->GetAnimInstance();
	if (instance && montage && characterstate == ECharacterState::ECS_ArmedSword) {
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
void AAliciaCharacter::RealeaseMouse0()
{
}
void AAliciaCharacter::PressMouse1()
{

	UAnimInstance* instance = GetMesh()->GetAnimInstance();
	if (instance && montage && characterstate == ECharacterState::ECS_ArmedSword && characterstate_montage == ECharacterState_montage::ECS_Idle) {
		/*
		FString s0 = FString("Defend ");
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
		}*/
		instance->Montage_Play(montage);
		int defendid = FMath::RandRange(0,2);
		if (defendid == 0)
		{
			instance->Montage_JumpToSection(FName("Defend"));
		}
		if (defendid == 1)
		{
			instance->Montage_JumpToSection(FName("Defend1"));
		}
		if (defendid == 2)
		{
			instance->Montage_JumpToSection(FName("Defend2"));
		}
		characterstate_montage = ECharacterState_montage::ECS_Playing;
	}
}
void AAliciaCharacter::RealeaseMouse1()
{
	UAnimInstance* instance = GetMesh()->GetAnimInstance();
	if (instance && montage && characterstate == ECharacterState::ECS_ArmedSword) {
		if (instance->Montage_IsPlaying(montage))
		{
			/*
			FString s0 = FString("Defend realease");
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
			}*/
			//instance->Montage_Stop(0.1f,montage);

			// 获取当前蒙太奇播放的片段名称
			FName CurrentSection = instance->Montage_GetCurrentSection(montage);

			// 检查是否是目标片段
			if (CurrentSection == FName("Defend")|| CurrentSection == FName("Defend1") || CurrentSection == FName("Defend2"))
			{
				instance->Montage_Stop(0.1f, montage);
			}
		}

		characterstate_montage = ECharacterState_montage::ECS_Idle;
	}
}
void AAliciaCharacter::PressKey1()
{

	if (sword && characterstate == ECharacterState::ECS_ArmedSword) {
		/*
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("press1"));
		}*/
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

void AAliciaCharacter::PressKeyQ()
{
}

void AAliciaCharacter::PressKeyR()
{
}

void AAliciaCharacter::PressKeyM()
{
}

void AAliciaCharacter::DisEquip()
{
	if (sword) {
		FAttachmentTransformRules rule(EAttachmentRule::SnapToTarget, true);
		sword->staticmesh->AttachToComponent(this->GetMesh(), rule, FName("Equipment_sword"));
		characterstate = ECharacterState::ECS_UNARMED;
	}

}

int AAliciaCharacter::GetHit(FVector impactpoint, AActor* attackactor, float damage)
{
	FVector forward = GetActorForwardVector();
	FVector hitdir = (attackactor->GetActorLocation() - GetActorLocation());
	hitdir.Z = 0;
	hitdir.Normalize();
	float cosdelta = forward.Dot(hitdir);
	float dir = forward.Cross(hitdir).Z;
	if (characterstate_montage == ECharacterState_montage::ECS_StartDefend) {
		if (cosdelta > 0) {
			return 2;
		}

	}
	else if (characterstate_montage == ECharacterState_montage::ECS_Defend)
	{
		if (cosdelta > 0 && damage < csc->defence) {
			//return 1;
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
			damage = damage * 0.5;
		}
		csc->TakeDamage(damage);
	}
	/*
	if (csc) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("Take damage"));
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
		FString::Printf(TEXT("damage: %.1f"),
			damage)
	);*/
	if ( csc) {

		if (csc->health <= 0) {
			characterstate_montage = ECharacterState_montage::ECS_Playing;
			if (hitmontage)
			{
				anim->Montage_Play(hitmontage);
				anim->Montage_JumpToSection(FName("Death"));
				TArray<UActorComponent*> Components;
				GetComponents(Components);
				//FInputModeGameAndUI InputMode;
				//UGameplayStatics::SetGamePaused(GetWorld(), true);
				FInputModeUIOnly InputMode;
				AAliciaPlayerController* apc = Cast<AAliciaPlayerController>(GetController());
				apc->SetInputMode(InputMode);
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

	return 1;
}

void AAliciaCharacter::PressKeyG()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("pressG"));
	}
	if (sword && characterstate == ECharacterState::ECS_ArmedSword) {
		sword->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		sword = nullptr;
	}

}

void AAliciaCharacter::PressKeyP()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("PressKeyP"));
	}
	OpenCloseCharMenu();
}

void AAliciaCharacter::Roll(const FInputActionValue& Value)
{
	// input is a Vector2D
	float RollValue = Value.Get<float>();

	if (CameraBoom != nullptr)
	{
		CameraBoom->TargetArmLength -= RollValue*10.f;
	}
}

void AAliciaCharacter::PressKeyTab()
{

}
void AAliciaCharacter::PressKeyEsc()
{
	if (AAliciaPlayerController* apc = Cast<AAliciaPlayerController>(GetController()))
	{
		AAliciaHUD* ah = Cast<AAliciaHUD>(apc->GetHUD());
		if (ah)
		{
			if (ah->IsStackEmpty())
			{
				ah->OpenGameMenu();
			}
			else
			{
				ah->EseAction();
			}
		}
	}
}
void AAliciaCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	FString s = OtherActor->GetName();
	FString s0 = FString("begin overlap:")+s;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
	}
	*/
}
void AAliciaCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*
	FString s = OtherActor->GetName();
	FString s0 = FString("end overlap:") + s;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
	}*/
}

UCharacterStateComponent* AAliciaCharacter::GetCsc()
{
	return csc;
}