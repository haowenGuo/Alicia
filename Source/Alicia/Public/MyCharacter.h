// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include"CharacterState.h"
#include "Interface/HitInterface.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
UCLASS()
class ALICIA_API AMyCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Turn(float value);
	void LookUp(float value);
	void MoveForward(float value);
	void MoveRight(float value);
	void MyJump();
	void PressE();
	void PressMouse0();
	void PressMouse1();
	void RealeaseMouse1();
	void PressKey1();
	void PressKeyG();
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springarm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* spherecollision;

	UPROPERTY(VisibleAnywhere)
	class UCharacterStateComponent* csc;
	
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* widgecomponent;
	
	UPROPERTY(VisibleAnywhere)
	class AMyActor* pickup_item;

	UPROPERTY(BlueprintReadWrite)
	class AMyActor* sword;

	UPROPERTY(BlueprintReadWrite)
	class AMyActor* bow;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* montage;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* equip_montage;

	UPROPERTY()
	class UEnemyWidget* uw;
	/*
	* 
	DYNAMIC_MULTICAST_SPARSE_DELEGATE_SixParams(FComponentBeginOverlapSignature, UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);
	DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams(FComponentEndOverlapSignature, UPrimitiveComponent, OnComponentEndOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex);
*/
	UFUNCTION()
	virtual void OnBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCharacterStateComponent* GetCsc() ;
	UPROPERTY(BlueprintReadWrite)
	bool jumping = false;

	UPROPERTY(BlueprintReadWrite)
	ECharacterState characterstate = ECharacterState::ECS_UNARMED;

	UPROPERTY(BlueprintReadWrite)
	ECharacterState_montage characterstate_montage = ECharacterState_montage::ECS_Idle;

	bool GetJumping() { return jumping; }

	UFUNCTION()
	ECharacterState_montage GetCharacterState_montage() { return characterstate_montage; }

	UFUNCTION()
	void SetCharacterState_montage(ECharacterState_montage state) { characterstate_montage= state; }

	UFUNCTION()
	void DisEquip();

	int SetPickupItem(AMyActor* item) { pickup_item = item; return 1; }

	virtual int GetHit(FVector impactpoint, AActor* attackactor, float damage) override;


	AMyActor* GetPickupItem() { return pickup_item; }

	UPROPERTY(EditAnywhere)
	class UAnimMontage* hitmontage;

	UPROPERTY(EditAnywhere)
	class USoundBase* hitsound;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* hitparticle;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* hitparticle2;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* deathmontage;
};
