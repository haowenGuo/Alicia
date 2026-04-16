// Fill out your copyright notice in the Description page of Project Settings.


#include "Inv_Widgets/Space/Inv_EquipGridInv.h"
#include "Inv_Widgets/Space/Inv_GridSlot.h"
UInv_EquipGridInv::UInv_EquipGridInv()
{
	EquipmentsIndex.Reserve(11);
	for (int i = 0; i < 11; i++)
	{
		EquipmentsIndex.Add(-1);
	}
}
int UInv_EquipGridInv::Equip( UInv_Item* item)
{
	EInv_EquipCategory EquipCategory = item->EquipCategory;
	int32 EquipIndex = static_cast<int>(EquipCategory);
	for (int32 i = 0; i < GridSlots.Num(); i++)
	{
		if (item == GridSlots[i]->item)
		{
			EquipmentsIndex[EquipIndex] = i;
			GridSlots[i]->ShowBorder();
		}
		else if (EquipCategory == GridSlots[i]->item->EquipCategory)
		{
			GridSlots[i]->CloseBorder();
		}
	}

	return 1;
}

int UInv_EquipGridInv::UnEquip( UInv_Item* item)
{
	EInv_EquipCategory EquipCategory = item->EquipCategory;
	int32 EquipIndex = static_cast<int>(EquipCategory);
	for (int32 i = 0; i < GridSlots.Num(); i++)
	{
		if (item == GridSlots[i]->item)
		{
			EquipmentsIndex[EquipIndex] = -1;
			GridSlots[i]->CloseBorder();
		}
	}

	return 1;
}

UInv_Item* UInv_EquipGridInv::GetEquipment(EInv_EquipCategory EquipCategory)
{
	int32 EquipIndex = static_cast<int32>(EquipCategory);
	return GridSlots[EquipmentsIndex[EquipIndex]]->item;

}

bool UInv_EquipGridInv::IsEquip(UInv_Item* item)
{
	if (item == GetEquipment(item->EquipCategory))
	{
		return true;
	}
	return false;
}
