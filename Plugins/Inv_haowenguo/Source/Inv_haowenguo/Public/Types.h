
#pragma once
#include"Types.generated.h"
/**
 * 
 */
UENUM()
enum class EInv_ItemCategory :uint8
{
	Equippable,
	Consumable,
	Material,
	WorkItem
};

UENUM()
enum class EInv_EquipCategory :uint8
{
	None,
	LeftHandWeapon,
	RightHandWeapon,
	Head,
	Hand,
	UpperBody,
	LowerBody,
	Arm,
	Foot,
	Ring,
	Neck
};

UENUM()
enum class EInv_PickUpCategory :uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};
USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()
public:
	FInv_SlotAvailability() {};
	FInv_SlotAvailability(int32 ItemIndex,int32 Room,bool bHasItem):Index(ItemIndex),AmoutToFill(Room), bItemAtIndex(bHasItem) {}
	int32 Index{ INDEX_NONE };
	int32 AmoutToFill{ 0 };
	bool bItemAtIndex{ false };
};


USTRUCT()
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()
public:
	FInv_SlotAvailabilityResult() {};

	TWeakObjectPtr<class UInv_Item> Item;
	int32 TotalRoomToFill{ 0 };
	int32 Remainder{ 0 };
	bool bStackable{ false };
	TArray<FInv_SlotAvailability>SlotAvailabilities;
	








};