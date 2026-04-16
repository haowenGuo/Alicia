// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Sword.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/HitInterface.h"
#include"CharacterStateComponent.h"

#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystems/AliciaAttributeSet.h>
#include <AbilitySystems/AliciaAbilitySystemComponent.h>
#include <Enemies/Enemy.h>
ASword::ASword()
{
	boxcollision = CreateDefaultSubobject<UBoxComponent>(FName("boxcollision"));
	start = CreateDefaultSubobject<USceneComponent>(FName("start"));
	end = CreateDefaultSubobject<USceneComponent>(FName("end"));
	boxcollision->SetupAttachment(GetRootComponent());
	start->SetupAttachment(GetRootComponent());
	end->SetupAttachment(GetRootComponent());
}
void ASword::BeginPlay()
{
	Super::BeginPlay();
	boxcollision->OnComponentBeginOverlap.AddDynamic(this, &ASword::OnBoxBeginOverlap);
	boxcollision->OnComponentEndOverlap.AddDynamic(this, &ASword::OnBoxEndOverlap);
	boxcollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ASword::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	AAliciaCharacter* player = Cast<AAliciaCharacter>(OtherActor);
	if (player) {
		player->SetPickupItem(this);
		//FAttachmentTransformRules rule(EAttachmentRule::SnapToTarget, true);
		//staticmesh->AttachToComponent(player->GetMesh(), rule, FName("RightHandSword"));
	}
}
void ASword::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex );
	AAliciaCharacter* player = Cast<AAliciaCharacter>(OtherActor);
	if (player) {
		player->SetPickupItem(nullptr);
		//FAttachmentTransformRules rule(EAttachmentRule::SnapToTarget, true);
		//staticmesh->AttachToComponent(player->GetMesh(), rule, FName("RightHandSword"));
	}
}

void ASword::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	FString s2 = OtherActor->GetName();
	/*
	FString s0 = FString("box voerlap:") + s2;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
	}*/
	if (start && end)
	{
		FVector s = start->GetComponentLocation();
		FVector e = end->GetComponentLocation();
		FRotator rot = start->GetComponentRotation();
		FHitResult hitresult;
		TArray<AActor*>toignore;
		toignore.Add(this);
		toignore.Add(owner);
		for (AActor* x : collisionacotrs) {
			toignore.Add(x);
		}
		FVector halfsize(TarceSize, TarceSize, TarceSize);
		UKismetSystemLibrary::BoxTraceSingle(this, s, e, halfsize, rot, ETraceTypeQuery::TraceTypeQuery1, false, toignore, EDrawDebugTrace::None, hitresult, true);
		if (hitresult.GetActor()) {

			collisionacotrs.Add(hitresult.GetActor());
			IHitInterface* otheractor=Cast<IHitInterface>(hitresult.GetActor());
			if (otheractor) {
				float damage = 0.f;
				AAliciaCharacterBase* charbase=nullptr;
				if (IsValid(GetSwordOwner()))
				{
					charbase = Cast<AAliciaCharacterBase>(GetSwordOwner());
				}
				if (charbase) {
					UAttributeSet* AttributeSet=charbase->GetAttributeSet();
					if (AttributeSet)
					{
						UAliciaAttributeSet* AliciaAttributeSet =Cast<UAliciaAttributeSet>(AttributeSet);
						if (AliciaAttributeSet)
						{
							damage = AliciaAttributeSet->GetAttack();
						}
					}
					
				}
				/*
				if (owner->GetCsc()) {
					damage += owner->GetCsc()->attack;
				}*/
				FVector impactpoint = hitresult.ImpactPoint;
				OnWeaponImpact(hitresult);
				int hitdefend = otheractor->GetHit(impactpoint,owner,damage);
				if (hitdefend == 2) {
					IHitInterface* hitactor = Cast<IHitInterface>(owner);
					if (hitactor)
					{
						hitactor->GetHit(impactpoint, hitresult.GetActor(), -1.f);
					}
					//owner->GetHit(impactpoint, hitactor, -1.f);
				}
			}
		}
	}
}
void ASword::ClearCollisionActors(){
	collisionacotrs.Empty(5);
}

void ASword::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ResetAnimationSpeed();
}
void ASword::OnWeaponImpact(const FHitResult& Hit)
{
	if (owner) {
		// 获取当前播放的蒙太奇
		UAnimInstance* AnimInstance;
		if (Cast<AEnemy>(owner))
		{
			return;
			//AnimInstance = Cast<AEnemy>(owner)->GetMesh()->GetAnimInstance();
		}
		else if (Cast<AAliciaCharacter>(owner))
		{
			AnimInstance = Cast<AAliciaCharacter>(owner)->GetMesh()->GetAnimInstance();
		}
		else {
			AnimInstance = nullptr;
		}
		if (AnimInstance)
		{
			UAnimMontage* montage = AnimInstance->GetCurrentActiveMontage();
			if (montage)
			{
				// 减慢蒙太奇播放速度
				AnimInstance->Montage_SetPlayRate(montage, 0.1f);

				// 设置定时器恢复速度
				FTimerHandle TimerHandle_ResetAnimSpeed;
				GetWorldTimerManager().SetTimer(
					TimerHandle_ResetAnimSpeed,
					this,
					&ASword::ResetAnimationSpeed,
					0.2f,
					false
				);
			}
		}
	}

}

void ASword::ResetAnimationSpeed()
{

	UAnimInstance* AnimInstance=nullptr ;
	if (Cast<AEnemy>(owner))
	{
		AnimInstance = Cast<AEnemy>(owner)->GetMesh()->GetAnimInstance();
	}
	else if (Cast<AAliciaCharacter>(owner))
	{
		AnimInstance = Cast<AAliciaCharacter>(owner)->GetMesh()->GetAnimInstance();
	}
	else {
		AnimInstance = nullptr;
	}
	if (AnimInstance)
	{
		if (UAnimMontage* montage = AnimInstance->GetCurrentActiveMontage()) {
			// 恢复蒙太奇播放速度
			AnimInstance->Montage_SetPlayRate(AnimInstance->GetCurrentActiveMontage(), 1.0f);
		}
	}
}
void ASword::SetCollisionEnable(ECollisionEnabled::Type collisiontype)
{
	if (boxcollision)
	{
		boxcollision->SetCollisionEnabled(collisiontype);
	}
	
}

void ASword::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (Target != GetOwner())return;
	TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC == nullptr)return;

	check(GameplayEffectClass)
		FGameplayEffectContextHandle contexthandle = TargetASC->MakeEffectContext();
	contexthandle.AddSourceObject(this);
	FGameplayEffectSpecHandle effectspechandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, contexthandle);
	ageh= TargetASC->ApplyGameplayEffectSpecToSelf(*effectspechandle.Data.Get());
	
}

void ASword::RemoveEffect()
{
	if (TargetASC)
	{
		TargetASC->RemoveActiveGameplayEffect(ageh);
	}
	
}
