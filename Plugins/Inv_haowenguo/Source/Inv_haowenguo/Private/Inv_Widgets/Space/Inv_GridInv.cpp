// Fill out your copyright notice in the Description page of Project Settings.


#include "Inv_Widgets/Space/Inv_GridInv.h"
#include"Inv_Widgets/Space/Inv_GridSlot.h"
#include"Components/CanvasPanel.h"
#include"Components/CanvasPanelSlot.h"
#include"InvManager/InvManagerComponent.h"
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Alica_Inv_PlayerController.h>
void UInv_GridInv::NativeOnInitialized()
{
	Super::NativeOnInitialized();



	ConstructGrid();
}

void UInv_GridInv::NativeConstruct()
{
	Super::NativeConstruct();
	AAlica_Inv_PlayerController* playcontoller = Cast<AAlica_Inv_PlayerController>(GetOwningPlayer());
	if (playcontoller)
	{
		UE_LOG(LogTemp, Display, TEXT("BIND OnItemAdded ENENT"));
		check(playcontoller->GetInvManager());
		playcontoller->GetInvManager()->OnItemAdded.AddDynamic(this, &UInv_GridInv::AddGridSlot);
		playcontoller->GetInvManager()->OnItemRemoved.AddDynamic(this, &UInv_GridInv::RemoveGridSlot);
	}


}

void UInv_GridInv::ConstructGrid()
{
	//UE_LOG(LogTemp, Display, TEXT("------------------------------"));

	/*
	GridSlots.Reserve(GridRows*GridColumns);

	for (int32 i = 0; i < GridRows; ++i) {
		for (int32 j = 0; j < GridColumns; ++j) {
			UInv_GridSlot* gridso = CreateWidget<UInv_GridSlot>(this,GridSlotClass);
			GridCanvasPanel->AddChild(gridso);

			const FIntPoint slotpoint(j,i);
			gridso->SetIndex(j + i * GridColumns);
			UCanvasPanelSlot* canvasslot = UWidgetLayoutLibrary::SlotAsCanvasSlot(gridso);
			canvasslot->SetSize(FVector2D(SlotSize));
			canvasslot->SetPosition(slotpoint * SlotSize);

			GridSlots.Add(gridso);
		}
	}*/
}

void UInv_GridInv::AddGridSlot(UInv_Item* item,int32 num)
{

	if (!item)return;
	if (item->ItemCategory != GetCategory())return;
	UE_LOG(LogTemp, Display, TEXT("Add a item"));
	for (auto slot : GridSlots)
	{
		if (slot->item->ItemName.Equals(item->ItemName) )
		{
			slot->AddStackNumber(1);
			return;
		}
	}
	
	UInv_GridSlot* gridso = CreateWidget<UInv_GridSlot>(this, GridSlotClass);
	gridso->InitItem(item);
	GridCanvasPanel->AddChild(gridso);
	gridso->SetParent(this);
	const FIntPoint slotpoint(GridSlots.Num() % GridColumns, GridSlots.Num() / GridColumns);
	gridso->SetIndex(GridSlots.Num());
	gridso->AddStackNumber(1);
	UCanvasPanelSlot* canvasslot = UWidgetLayoutLibrary::SlotAsCanvasSlot(gridso);
	canvasslot->SetSize(FVector2D(SlotSize));
	canvasslot->SetPosition(slotpoint * SlotSize*1.1f);

	GridSlots.Add(gridso);
}

void UInv_GridInv::RemoveGridSlot(UInv_Item* item,int32 num)
{
	if (!item)return;
	if (num<=0)return;
	if (item->ItemCategory != GetCategory())return;
	UE_LOG(LogTemp, Display, TEXT("Add a item"));
	for (auto slot : GridSlots)
	{
		if (slot->item->ItemName.Equals(item->ItemName))
		{
			if (slot->StackNumber > num) {
				slot->SubtackNumber(num);
			}
			else {
				GridSlots.Remove(slot);
				GridCanvasPanel->RemoveChild(slot);
				RefreshGridSlot();
			}

		}
	}
	
}

void UInv_GridInv::RefreshGridSlot()
{
	for (int i = 0; i < GridSlots.Num(); i++)
	{
		//GridCanvasPanel->RemoveChild(GridSlots[i]);
		//GridCanvasPanel->AddChild(GridSlots[i]);

		const FIntPoint slotpoint(i % GridColumns, i / GridColumns);
		GridSlots[i]->SetIndex(SlotNumber);
		UCanvasPanelSlot* canvasslot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlots[i]);
		canvasslot->SetSize(FVector2D(SlotSize));
		canvasslot->SetPosition(slotpoint * SlotSize);
	}

}

void UInv_GridInv::SetParent(UInv_SpaceInv* widget)
{
	Parent = widget;
}
