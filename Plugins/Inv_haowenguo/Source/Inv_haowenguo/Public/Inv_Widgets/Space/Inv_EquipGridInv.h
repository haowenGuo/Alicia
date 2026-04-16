// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inv_Widgets/Space/Inv_GridInv.h"
#include "Inv_EquipGridInv.generated.h"

/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UInv_EquipGridInv : public UInv_GridInv
{
	GENERATED_BODY()
public:
	UInv_EquipGridInv();
	TArray<int32> EquipmentsIndex;
	int32 Equip(UInv_Item* item);

	int32 UnEquip(UInv_Item* item);

	UInv_Item* GetEquipment(EInv_EquipCategory EquipCategory);

	bool IsEquip(UInv_Item* item);
};
