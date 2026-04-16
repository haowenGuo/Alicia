// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActor.h"
#include "Sword2.generated.h"

/**
 * 
 */
UCLASS()
class ALICIA_API ASword2 : public AMyActor
{
	GENERATED_BODY()
public:
	ASword2();
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

	class AEnemy* owner;

	TArray<AActor*>collisionacotrs;
public:

	UFUNCTION(BlueprintCallable)
	void SetSwordOwner(AEnemy* character) { owner = character; }

	UPROPERTY(EditAnywhere)
	float SwordAttack=1.f;

	void ResetAnimationSpeed();

	UFUNCTION(BlueprintCallable)
	void SetCollisionEnable(ECollisionEnabled::Type collisiontype);

	UFUNCTION(BlueprintCallable)
	void ClearCollisionActors();
};
