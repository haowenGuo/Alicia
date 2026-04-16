// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include"MyCharacter.h"
#include "GameplayEffectTypes.h"
#include <Alicia/AliciaCharacter.h>
#include "Sword.generated.h"

/**
 * 
 */
UCLASS()
class ALICIA_API ASword : public AMyActor
{
	GENERATED_BODY()
public:
	ASword();

protected:

	virtual void BeginPlay() override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OnWeaponImpact(const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxcollision;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* start;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* end;

	ACharacter* owner;

	TArray<AActor*>collisionacotrs;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TarceSize=5.f;

	FActiveGameplayEffectHandle ageh;

	class UAbilitySystemComponent* TargetASC;
public:

	UFUNCTION(BlueprintCallable)
	void SetSwordOwner(ACharacter* character) { owner = character; }

	UFUNCTION(BlueprintCallable)
	ACharacter* GetSwordOwner() { return owner ; }

	void ResetAnimationSpeed();

	UFUNCTION(BlueprintCallable)
	void SetCollisionEnable(ECollisionEnabled::Type collisiontype);

	UFUNCTION(BlueprintCallable)
	void ClearCollisionActors();

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void RemoveEffect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayEffects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;


};
