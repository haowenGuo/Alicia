// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EquippableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquippableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INV_HAOWENGUO_API IEquippableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 EquipRightWeapon(AActor* equipment);

	virtual int32 EquipLeftWeapon(AActor* equipment);

	virtual int32 EquipUpperBody(AActor* equipment);

	virtual int32 EquipLowerBody(AActor* equipment);

	virtual int32 EquipHead(AActor* equipment);

	virtual int32 EquipHand(AActor* equipment);

	virtual int32 EquipArm(AActor* equipment);

	virtual int32 EquipFoot(AActor* equipment);

	virtual int32 EquipRing(AActor* equipment);

	virtual int32 EquipNeck(AActor* equipment);


	virtual int32 UnEquipRightWeapon();

	virtual int32 UnEquipLeftWeapon();

	virtual int32 UnEquipUpperBody();

	virtual int32 UnEquipLowerBody();

	virtual int32 UnEquipHead();

	virtual int32 UnEquipHand();

	virtual int32 UnEquipArm();

	virtual int32 UnEquipFoot();

	virtual int32 UnEquipRing();

	virtual int32 UnEquipNeck();
};
