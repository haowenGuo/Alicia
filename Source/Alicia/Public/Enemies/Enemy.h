// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "Perception/PawnSensingComponent.h"
#include "CharacterState.h"
#include <Enemies/Sword2.h>
#include <Weapons/Sword.h>
#include "AliciaCharacterBase.h"
#include "Enemy.generated.h"

UCLASS()
class ALICIA_API AEnemy : public AAliciaCharacterBase ,public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSeenPawn(APawn* Pawn);

	UFUNCTION()
	void OnHearNoise(APawn* Pawn, const FVector& Location, float Volume);


	UFUNCTION()
	void Detect();


	UFUNCTION()
	void Fight();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual int GetHit(FVector impactpoint, AActor* attackactor, float damage) override;

	UFUNCTION(BlueprintCallable)
	FVector GetWarpRotation();

	UFUNCTION(BlueprintCallable)
	FVector GetWarpTranslation();

	void DisplayUW() ;
	class UCharacterStateComponent* GetCsc();
	void StartPatrol();
	void EndPatrol();
	void Patroling();
	UPROPERTY()
	FTimerHandle DetectHandle;
	UPROPERTY()
	FTimerHandle FightHandle;
	UPROPERTY()
	FTimerHandle PatrolHandle;

	UPROPERTY(EditAnywhere)
	float MinDetectPeriod = .3f;

	UPROPERTY(EditAnywhere)
	float MaxDetectPeriod = 1.f;

	UPROPERTY(EditAnywhere)
	float fightperiod = .3f;

	UPROPERTY(EditAnywhere)
	float ignorerange = 2000.f;

	UPROPERTY(EditAnywhere)
	float chasingrange = 1000.f;

	UPROPERTY(EditAnywhere)
	float fightingrange = 300.f;

	UPROPERTY(EditAnywhere)
	float attackrange = 300.f;

	UPROPERTY(EditAnywhere)
	float warpdistance = 300.f;
	UPROPERTY(VisibleAnywhere)
	class UCharacterStateComponent* csc;

	UPROPERTY(VisibleAnywhere)
	class UEnemyAIComponent* eaiconponent;

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* sensing;
	
	UPROPERTY(VisibleAnywhere)
	class AAIController* aicontrol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> patrolpoints;

	int patrolpointid=0;
	UPROPERTY(EditAnywhere)
	float maxspeed = 300.f;
	UPROPERTY(EditAnywhere)
	float minspeed = 0.f;
	UPROPERTY(EditAnywhere)
	float walkspeed = 100.f;
	UPROPERTY(EditAnywhere)
	float runspeed = 200.f;

	UPROPERTY(EditAnywhere)
	float mindistance = 500.f;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* widgecomponent;

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

	UPROPERTY(EditAnywhere)
	class UAnimMontage* attackmontage;

	UPROPERTY()
	class UEnemyWidget* uw;

	UPROPERTY()
	class UNiagaraComponent* niagaracomponent;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadWrite)
	EEnemyState enemystate = EEnemyState::EES_Idle;
	
	UPROPERTY(BlueprintReadWrite)
	class AAliciaCharacter* target;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ASword> sword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASword>RightSwordClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ASword> Leftsword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASword>LeftSwordClass;
};
