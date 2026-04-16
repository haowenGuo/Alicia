// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include"CharacterStateComponent.h"
#include "Components/WidgetComponent.h"
#include <Widges/EnemyWidget.h>
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include <MyCharacter.h>
#include <MyActor.h>

#include<Alicia/AliciaCharacter.h>
#include"Enemies/EnemyAIComponent.h"
#include <AbilitySystems/AliciaAbilitySystemComponent.h>
#include <AbilitySystems/AliciaAttributeSet.h>
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	niagaracomponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("niagaracomponent"));
	niagaracomponent->SetupAttachment(GetRootComponent());
	csc = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("characterstatecomponent"));
	widgecomponent= CreateDefaultSubobject<UWidgetComponent>(TEXT("widgecomponent"));
	widgecomponent->SetupAttachment(GetRootComponent());
	widgecomponent->SetVisibility(false);
	sensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("sensingcomponent"));
	eaiconponent= CreateDefaultSubobject<UEnemyAIComponent>(TEXT("eaiconponent"));
	AbilitySystemCompont = CreateDefaultSubobject<UAliciaAbilitySystemComponent>(TEXT("EnemyAbilitySystemComponent"));
	AbilitySystemCompont->SetIsReplicated(true);
	AbilitySystemCompont->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAliciaAttributeSet>(TEXT("EnemyAttributeSet"));
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemCompont->InitAbilityActorInfo(this,this);
	uw = Cast<UEnemyWidget>(widgecomponent->GetUserWidgetObject());
	aicontrol = Cast<AAIController>(GetController());
	sensing->OnSeePawn.AddDynamic(this, &AEnemy::OnSeenPawn);
	DetectHandle.Invalidate();
	FightHandle.Invalidate();
	if (csc)
	{
		csc->InitCsc(AbilitySystemCompont, AttributeSet);
	}
	if (patrolpoints.Num() > 0) {
		StartPatrol();
		enemystate = EEnemyState::EES_Patrol;
	}
	if (RightSwordClass) {
		FVector LOC = GetActorLocation() + GetActorForwardVector() * 100.f;;
		FRotator RO = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.Owner = Cast<AActor>(this);
		sword = GetWorld()->SpawnActor<ASword>(RightSwordClass, SpawnParams);
		FAttachmentTransformRules rule(EAttachmentRule::SnapToTarget, true);
		sword->AttachToComponent(this->GetMesh(), rule, FName("RightHandSword"));
		sword->SetSwordOwner(this);
	}
	if (LeftSwordClass) {
		FVector LOC = GetActorLocation() + GetActorForwardVector() * 100.f;;
		FRotator RO = GetActorRotation();
		FActorSpawnParameters SpawnParams; 
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnParams.Owner = Cast<AActor>(this);
		Leftsword = GetWorld()->SpawnActor<ASword>(LeftSwordClass, SpawnParams);
		FAttachmentTransformRules rule(EAttachmentRule::SnapToTarget, true);
		Leftsword->AttachToComponent(this->GetMesh(), rule, FName("LeftHandSword"));
		Leftsword->SetSwordOwner(this);
	}
	
}
void AEnemy::OnSeenPawn( APawn* Pawn) {
	target = Cast<AAliciaCharacter>(Pawn);
	

	if (target) {
		/*
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 5, FColor::Blue, FString::Printf(TEXT("on seen player")));
		}*/
		/*
		if (DetectHandle.IsValid())
		{
			return;
		}*/
		Detect();
		/*
		GetWorldTimerManager().SetTimer(
			DetectHandle,
			this,
			&AEnemy::Detect,
			detectperiod,
			true
		);*/

	}
}
void AEnemy::OnHearNoise( APawn* Pawn, const FVector& Location, float Volume) {
	if (Volume < 10.f) {

		return;
	}
	AAliciaCharacter* player = Cast<AAliciaCharacter>(Pawn);
	if (player) {
		FAIMoveRequest mrq;
		mrq.SetGoalActor(player);
		mrq.SetAcceptanceRadius(mindistance - 100.f);
		mrq.SetProjectGoalLocation(true);
		mrq.SetUsePathfinding(true);
		if (aicontrol) {
			aicontrol->MoveTo(mrq);
		}
	}
}
void AEnemy::Detect()
{
	double period = FMath::RandRange(MinDetectPeriod, MaxDetectPeriod);
	GetWorldTimerManager().SetTimer(
		DetectHandle,
		this,
		&AEnemy::Detect,
		period,
		false
	);
	if (enemystate == EEnemyState::EES_Attacking || enemystate == EEnemyState::EES_GetHit) {
		return;
	}
	FAIMoveRequest mrq;
	if (target) {
		if (enemystate == EEnemyState::EES_Dead ) { return; }
		float dis = 0.f;
		dis = (GetActorLocation() - target->GetActorLocation()).Size();
		if (dis >= ignorerange) {
			//检测到在战斗忽视半径外，敌人状态变为IDLE或PATROL，清空周期检测定时器
			StartPatrol();
			if (DetectHandle.IsValid()) {
				GetWorldTimerManager().ClearTimer(DetectHandle);
			}
			
		}
		else if (dis >= chasingrange) {
			//检测到在追击半径外，敌人状态变为Approach，清空周期检测定时器
			enemystate=EEnemyState::EES_Approach;
			EndPatrol();

			GetCharacterMovement()->MaxWalkSpeed = walkspeed;
			mrq.SetGoalActor(target);
			mrq.SetAcceptanceRadius(chasingrange - 300.f);
			mrq.SetProjectGoalLocation(true);
			mrq.SetUsePathfinding(true);
			if (aicontrol) {
				aicontrol->MoveTo(mrq);
			}
		}
		else if (dis >= fightingrange) {
			/*
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString("fightingrange"));
			GEngine->AddOnScreenDebugMessage(
				-1, // 调试消息槽位（-1表示自动分配，避免覆盖）
				0.5f, // 显示时长（秒）
				FColor::Blue, // 文本颜色
				FString::Printf(TEXT("attackrange: % f, 当前距离: % f"), attackrange, dis));*/
			//检测到在战斗半径外，敌人状态变为Chasing，清空周期检测定时器
			enemystate = EEnemyState::EES_Chasing;
			EndPatrol();

			GetCharacterMovement()->MaxWalkSpeed =runspeed;
			mrq.SetGoalActor(target);
			mrq.SetAcceptanceRadius(fightingrange - 50.f);
			mrq.SetProjectGoalLocation(true);
			mrq.SetUsePathfinding(true);
			if (aicontrol) {
				aicontrol->MoveTo(mrq);
			}
		}
		else  if (dis >= attackrange) {
			/*
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString("attackrange"));
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue,
				FString::Printf(TEXT("attackrange: %.1f, 当前距离: %.1f, 接受半径: %.1f"),
					attackrange, dis, attackrange - 100.f)
			);
			*/
			GetCharacterMovement()->MaxWalkSpeed = maxspeed;
			enemystate = EEnemyState::EES_Fight;
			EndPatrol();

			mrq.SetGoalActor(target);
			mrq.SetAcceptanceRadius(attackrange-100.f);
			mrq.SetProjectGoalLocation(true);
			mrq.SetUsePathfinding(true);
			if (aicontrol) {
				aicontrol->MoveTo(mrq);
			}

		}
		else {
			//GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("fight"));
			if (!FightHandle.IsValid()) {
				Fight();
				GetWorldTimerManager().SetTimer(
					FightHandle,
					this,
					&AEnemy::Fight,
					fightperiod,
					true
				);
			}
			

		}
	}
	else {
		
	}

	return;
}
void AEnemy::Fight()
{
	/*
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("fighting"));
	}*/
	if (target) {
		float dis = 0.f;
		dis = (GetActorLocation() - target->GetActorLocation()).Size();
		if (dis >= attackrange) {
			//检测到在战斗忽视半径外，敌人状态变为IDLE或PATROL，清空周期检测定时器
			if (FightHandle.IsValid()) {
				GetWorldTimerManager().ClearTimer(FightHandle);
			}

		}
	}
	int attackid = FMath::RandRange(0,3);

	if (enemystate == EEnemyState::EES_Attacking || enemystate == EEnemyState::EES_GetHit) {
		return;
	}

/**/
	UAnimInstance* anim = GetMesh()->GetAnimInstance();
	if (attackmontage && anim) {
		
		//FVector forward = GetActorForwardVector();
		anim->Montage_Play(attackmontage);
		enemystate = EEnemyState::EES_Attacking;
		switch (attackid)
		{
		case 0:
			anim->Montage_JumpToSection("Attack0");

			break;
		case 1:
			anim->Montage_JumpToSection("Attack1");
			break;
		case 2:
			anim->Montage_JumpToSection("Attack2");
			break;
		case 3:
		{
			anim->Montage_JumpToSection("Attack3");
			break;
		}

		default:
			break;
		}
	}
}
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSeePawnDelegate, APawn*, Pawn);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHearNoiseDelegate, APawn*, Instigator, const FVector&, Location, float, Volume);
// 
// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (enemystate==EEnemyState::EES_Fight  || enemystate == EEnemyState::EES_Attacking) {
		if (target) {
			FVector Direction = target->GetActorLocation() - GetActorLocation();
			Direction.Normalize();
			// 计算目标旋转
			FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
			// 平滑旋转
			FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, .5f);
			NewRotation.Roll = 0.f;
			NewRotation.Pitch = 0.f;
			
			SetActorRotation(NewRotation);
		}
	}
	else if (enemystate == EEnemyState::EES_Searching) {
		FVector right = GetActorRightVector();
		FRotator TargetRotation = FRotationMatrix::MakeFromX( right).Rotator();
		// 平滑旋转
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, .6f);
		NewRotation.Roll = 0.f;
		NewRotation.Pitch = 0.f;
		SetActorRotation(NewRotation);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int AEnemy::GetHit(FVector impactpoint, AActor* attackactor, float damage)
{
	if (Cast<AEnemy>(attackactor))return 1;;
	UAnimInstance* anim = GetMesh()->GetAnimInstance();
	FVector forward = GetActorForwardVector();
	FVector hitdir = (impactpoint - GetActorLocation());
	hitdir.Z = 0;
	hitdir.Normalize();
	float cosdelta = forward.Dot(hitdir);
	float dir = forward.Cross(hitdir).Z;
	if (enemystate != EEnemyState::EES_Attacking || damage==-1.f) {
		
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
			anim->Montage_Play(hitmontage);
			anim->Montage_JumpToSection(direction);
			enemystate = EEnemyState::EES_GetHit;
	}

	}
	//enemystate = EEnemyState::EES_Searching;
	if (hitsound) {
		UGameplayStatics::PlaySoundAtLocation(this,hitsound, impactpoint);
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
	if (uw) {
		uw->AddToViewport();
		// 设置定时器恢复速度
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&AEnemy::DisplayUW,
			8.f,
			false
		);
	}
	if (csc) {
		damage = abs(damage);
		csc->TakeDamage(damage);
	}
	if (uw && csc) {
		
		uw->SetHealth( csc->GetHealthPercent());
		if (csc->health <= 0) {
			enemystate = EEnemyState::EES_Dead;
			GetWorldTimerManager().ClearTimer(DetectHandle);
			GetWorldTimerManager().ClearTimer(PatrolHandle);
			GetWorldTimerManager().ClearTimer(FightHandle);
			uw->RemoveFromParent();
			GetCharacterMovement()->MaxWalkSpeed = 0.f;
			if (deathmontage)
			{
				anim->Montage_Play(deathmontage);
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
		else
		{
			OnSeenPawn(Cast<APawn>(attackactor));
		}
	}
	/*
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString("get hit"));
	}*/
	return 1;
}

FVector AEnemy::GetWarpRotation()
{
	if (target) {
		return target->GetActorLocation();
	}
	return FVector();
}

FVector AEnemy::GetWarpTranslation()
{
	if (target) {
		FVector targetlocation = target->GetActorLocation();
		FVector Direction = GetActorLocation() - target->GetActorLocation();
		Direction=Direction.GetSafeNormal();
		return targetlocation + Direction * warpdistance;
	}

	return FVector();
}

void AEnemy::DisplayUW()
{
	uw->RemoveFromParent();
}

void AEnemy::StartPatrol()
{
	if (patrolpoints.Num() > 0) {
		if (enemystate == EEnemyState::EES_Patrol)
		{
			return;
		}
		enemystate = EEnemyState::EES_Patrol;
		GetCharacterMovement()->MaxWalkSpeed=walkspeed;
		patrolpointid = ((patrolpointid +1) % (2*patrolpoints.Num()));
		FAIMoveRequest mrq;
		if (patrolpointid < patrolpoints.Num() && patrolpointid>=0) {
			mrq.SetGoalActor(patrolpoints[patrolpointid]);
		}
		else if(patrolpointid >= patrolpoints.Num() && patrolpointid< (2 * patrolpoints.Num())) {
			mrq.SetGoalActor(patrolpoints[2 * patrolpoints.Num()-patrolpointid - 1]);
		}
		else {
			return;
		}
		
		mrq.SetAcceptanceRadius(mindistance - 200.f);
		mrq.SetProjectGoalLocation(true);
		mrq.SetUsePathfinding(true);
		if (aicontrol) {
			aicontrol->MoveTo(mrq);
		}
		GetWorldTimerManager().SetTimer(
			PatrolHandle,
			this,
			&AEnemy::Patroling,
			2.f,
			true
		);
	}
	else {
		enemystate = EEnemyState::EES_Idle;
		GetWorldTimerManager().ClearTimer(PatrolHandle);
	}
}
void AEnemy::EndPatrol()
{
	if (PatrolHandle.IsValid()) {
		GetWorldTimerManager().ClearTimer(PatrolHandle);
	}
	//GetCharacterMovement()->MaxWalkSpeed = maxspeed;
}
void AEnemy::Patroling()
{

	if (patrolpoints.Num() > 0) {

		float dis = 0.f;
		if (patrolpointid < patrolpoints.Num() && patrolpointid >= 0) {
			dis = (GetActorLocation() - (patrolpoints[patrolpointid]->GetActorLocation())).Size();
		}
		else if (patrolpointid >= patrolpoints.Num() && patrolpointid < (2 * patrolpoints.Num())) {
			dis = (GetActorLocation() - (patrolpoints[2 * patrolpoints.Num() - patrolpointid - 1]->GetActorLocation())).Size();
		}
		else {
			return;
		}
		/*
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, FString::Printf(TEXT("distance=     %f"),dis));
		}*/
		if (dis > mindistance) {
			return;
		}

		FAIMoveRequest mrq;
		patrolpointid = ((patrolpointid + 1) % (2 * patrolpoints.Num()));
		if (patrolpointid < patrolpoints.Num() && patrolpointid >= 0) {
			mrq.SetGoalActor(patrolpoints[patrolpointid]);
		}
		else if (patrolpointid >= patrolpoints.Num() && patrolpointid < (2 * patrolpoints.Num())) {
			mrq.SetGoalActor(patrolpoints[2 * patrolpoints.Num() - patrolpointid - 1]);
		}
		else {
			return;
		}
		mrq.SetAcceptanceRadius(mindistance - 100.f);
		mrq.SetProjectGoalLocation(true);
		mrq.SetUsePathfinding(true);
		if (aicontrol) {
			aicontrol->MoveTo(mrq);
		}
	}
}
UCharacterStateComponent*  AEnemy::GetCsc()
{
	return csc;
}
