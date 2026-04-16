// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/Inv_FastArray.h"
#include"InvManager/InvManagerComponent.h"

TArray<UInv_Item*>  FInv_InvFastArray::GetAllItems() const
{
	TArray<UInv_Item*>Results;
	Results.Reserve(Items.Num());
	for (const auto& item : Items) {
		if (!IsValid(item.Item))continue;
		Results.Add(item.Item);
	}
	return Results;

}


void FInv_InvFastArray::PreReplicateRemove(const TArrayView<int32> RemoveIndices, int32 FinalSize)
{
	UInvManagerComponent* IMC = Cast<UInvManagerComponent>(OwnerComponent);
	if (!IsValid(IMC))return;
	for (int32 Index : RemoveIndices) {
		IMC->OnItemRemoved.Broadcast(Items[Index].Item,1);
	}
}

void FInv_InvFastArray::PostReplicateAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UInvManagerComponent* IMC = Cast<UInvManagerComponent>(OwnerComponent);
	if (!IsValid(IMC))return;
	for (int32 Index : AddedIndices) {
		IMC->OnItemAdded.Broadcast(Items[Index].Item,1);
	}
}

UInv_Item* FInv_InvFastArray::AddItem(UInv_Item* item)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	FInv_ItemStruct& NewItem = Items.AddDefaulted_GetRef();
	NewItem.Item = item;

	MarkItemDirty(NewItem);
	return  item;
}

UInv_Item* FInv_InvFastArray::AddItem(PickUpComponent* pickupcomponent)
{
	return nullptr;
}

void FInv_InvFastArray::RemoveItem(UInv_Item* item)
{
	for (auto it = Items.CreateIterator(); it; ++it) {
		FInv_ItemStruct& is = *it;
		if (is.Item == item) {
			it.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}
