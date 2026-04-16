// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include"CharacterState.h"
#include "Interface/HitInterface.h"
#include "AliciaCharacterBase.h"
#include"InvInterfaces/EquippableInterface.h"
#include "AliciaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USphereComponent;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AAliciaCharacter : public AAliciaCharacterBase, public IHitInterface,public IEquippableInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* spherecollision;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	/** Defend Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DefendAction;

	/** E Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EAction;

	/** G Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GAction;

	/** M Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MAction;

	/** Q Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* QAction;

	/** R Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RAction;

	/** R Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PAction;

	/** R Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ESCAction;

	/** R Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TabAction;

	/** R Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RollAction;

	void PressE();
	void PressMouse0();
	void RealeaseMouse0();
	void PressMouse1();
	void RealeaseMouse1();
	void PressKey1();
	void PressKeyQ();
	void PressKeyR();
	void PressKeyM();
	void PressKeyG();
	void PressKeyP();
	void Roll(const FInputActionValue& Value);
	void PressKeyTab();
	void PressKeyEsc();
	void Jump() override;
	void StopJumping() override;
public:
	AAliciaCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void OpenCloseCharMenu();

	UPROPERTY(VisibleAnywhere)
	class UCharacterStateComponent* csc;

	UPROPERTY(VisibleAnywhere)
	class AMyActor* pickup_item;

	UPROPERTY(BlueprintReadWrite)
	class AMyActor* sword;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* montage;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* equip_montage;

	UPROPERTY(BlueprintReadWrite)
	ECharacterState characterstate = ECharacterState::ECS_UNARMED;

	UPROPERTY(BlueprintReadWrite)
	ECharacterState_montage characterstate_montage = ECharacterState_montage::ECS_Idle;

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


	UFUNCTION()
	ECharacterState_montage GetCharacterState_montage() { return characterstate_montage; }

	UFUNCTION()
	void SetCharacterState_montage(ECharacterState_montage state) { characterstate_montage = state; }

	UFUNCTION()
	void DisEquip();

	int SetPickupItem(AMyActor* item) { pickup_item = item; return 1; }

	virtual int GetHit(FVector impactpoint, AActor* attackactor, float damage) override;


	AMyActor* GetPickupItem() { return pickup_item; }

	UCharacterStateComponent* GetCsc();

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	virtual void PossessedBy(AController* NewController)override;

	virtual void OnRep_PlayerState()override;


	/**  Equip  **/
	virtual int32 EquipRightWeapon(AActor* equipment) override;

	virtual int32 EquipLeftWeapon(AActor* equipment) override;

	virtual int32 EquipUpperBody(AActor* equipment) override;

	virtual int32 EquipLowerBody(AActor* equipment) override;

	virtual int32 EquipHead(AActor* equipment) override;

	virtual int32 EquipHand(AActor* equipment) override;

	virtual int32 EquipArm(AActor* equipment) override;

	virtual int32 EquipFoot(AActor* equipment) override;

	virtual int32 EquipRing(AActor* equipment) override;

	virtual int32 EquipNeck(AActor* equipment) override;

	virtual int32 UnEquipRightWeapon() override;

	virtual int32 UnEquipLeftWeapon() override;

	virtual int32 UnEquipUpperBody() override;

	virtual int32 UnEquipLowerBody() override;

	virtual int32 UnEquipHead() override;

	virtual int32 UnEquipHand() override;

	virtual int32 UnEquipArm() override;

	virtual int32 UnEquipFoot() override;

	virtual int32 UnEquipRing() override;

	virtual int32 UnEquipNeck() override;

	/**  Equip  **/
};

