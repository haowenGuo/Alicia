// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Sword2.h"
#include "Weapons/Sword.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/HitInterface.h"
#include"Enemies/Enemy.h"
#include"CharacterStateComponent.h"

ASword2::ASword2()
{
	boxcollision = CreateDefaultSubobject<UBoxComponent>(FName("boxcollision"));
	start = CreateDefaultSubobject<USceneComponent>(FName("start"));
	end = CreateDefaultSubobject<USceneComponent>(FName("end"));
	boxcollision->SetupAttachment(GetRootComponent());
	start->SetupAttachment(GetRootComponent());
	end->SetupAttachment(GetRootComponent());
}
void ASword2::BeginPlay()
{
	Super::BeginPlay();
	boxcollision->OnComponentBeginOverlap.AddDynamic(this, &ASword2::OnBoxBeginOverlap);
	boxcollision->OnComponentEndOverlap.AddDynamic(this, &ASword2::OnBoxEndOverlap);
	boxcollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ASword2::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
void ASword2::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void ASword2::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FString s2 = OtherActor->GetName();
	/*
	FString s0 = FString("box voerlap:") + s2;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 30, FColor::Blue, s0);
	}
	*/
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
		FVector halfsize(50.f, 50.f, 50.f);
		UKismetSystemLibrary::BoxTraceSingle(this, s, e, halfsize, rot, ETraceTypeQuery::TraceTypeQuery1, false, toignore, EDrawDebugTrace::None, hitresult, true);
		AActor* hitactor= hitresult.GetActor();
		if (hitactor) {
			collisionacotrs.Add(hitactor);
			IHitInterface* otheractor = Cast<IHitInterface>(hitactor);
			if (otheractor) {
				float damage = SwordAttack;
				if (owner) {
					if (owner->GetCsc()) {
						damage += owner->GetCsc()->attack;
					}
				}
				
				FVector impactpoint = hitresult.ImpactPoint;
				OnWeaponImpact(hitresult);
				int hitdefend=otheractor->GetHit(impactpoint, owner, damage);
				if (hitdefend ==2) {
					owner->GetHit(impactpoint, hitactor, -1.f);
				}
			}
		}
	}
}
void ASword2::ClearCollisionActors() {
	collisionacotrs.Empty(5);
}

void ASword2::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ResetAnimationSpeed();
}
void ASword2::OnWeaponImpact(const FHitResult& Hit)
{
	/*
	if (owner) {
		// 获取当前播放的蒙太奇
		if (UAnimInstance* AnimInstance = owner->GetMesh()->GetAnimInstance())
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
					&ASword2::ResetAnimationSpeed,
					0.2f,
					false
				);
			}
		}
	}
	*/
}

void ASword2::ResetAnimationSpeed()
{
	UAnimInstance* AnimInstance = owner->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		if (UAnimMontage* montage = AnimInstance->GetCurrentActiveMontage()) {
			// 恢复蒙太奇播放速度
			AnimInstance->Montage_SetPlayRate(AnimInstance->GetCurrentActiveMontage(), 1.0f);
		}
	}
}
void ASword2::SetCollisionEnable(ECollisionEnabled::Type collisiontype)
{
	if (boxcollision)
	{
		boxcollision->SetCollisionEnabled(collisiontype);
	}

}
