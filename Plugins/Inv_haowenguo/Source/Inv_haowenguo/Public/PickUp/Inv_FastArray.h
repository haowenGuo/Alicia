#pragma once

#include "CoreMinimal.h"
#include <Net/Serialization/FastArraySerializer.h>
#include"Inv_Item.h"
#include"Inv_FastArray.generated.h"


class UInv_Item;
/**
* 库存Item结构体
* 用于实际储存库存对象
 *
 */
USTRUCT(BlueprintType)
struct FInv_ItemStruct :public FFastArraySerializerItem
{
	GENERATED_BODY()
public:
	FInv_ItemStruct() {}

	UPROPERTY()
	TObjectPtr<class UInv_Item> Item = nullptr;
};

//快速数组
USTRUCT(BlueprintType)
struct FInv_InvFastArray :public FFastArraySerializer
{
	GENERATED_BODY()

public:
	FInv_InvFastArray() :OwnerComponent(nullptr) {};

	FInv_InvFastArray(UActorComponent myOwnerComponent) :OwnerComponent(myOwnerComponent) {};

	TArray<UInv_Item*>  GetAllItems()const;

	//FFASTARRAY
	void PreReplicateRemove(const TArrayView<int32>RemoveIndices, int32 FinalSize);
	void PostReplicateAdd(const TArrayView<int32>AddedIndices, int32 FinalSize);

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FInv_ItemStruct, FInv_InvFastArray>(Items, DeltaParams, *this);
	}

	UInv_Item* AddItem(UInv_Item* item);
	UInv_Item* AddItem(class PickUpComponent* pickupcomponent);
	void RemoveItem(UInv_Item* item);

	UPROPERTY()
	TArray<FInv_ItemStruct>Items;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent>OwnerComponent;

};
template<>
struct TStructOpsTypeTraits<FInv_InvFastArray> :public TStructOpsTypeTraitsBase2<FInv_InvFastArray>
{
	enum { WithNetDealtaSerialzer = true };
};

