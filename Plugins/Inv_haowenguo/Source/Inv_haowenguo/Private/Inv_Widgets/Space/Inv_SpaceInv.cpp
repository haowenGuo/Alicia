// Fill out your copyright notice in the Description page of Project Settings.


#include "Inv_Widgets/Space/Inv_SpaceInv.h"
#include"Components/Button.h"
void UInv_SpaceInv::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Mate->OnClicked.AddDynamic(this,&UInv_SpaceInv::ShowMate);

	Button_Work->OnClicked.AddDynamic(this, &UInv_SpaceInv::ShowWork);

	Button_Equip->OnClicked.AddDynamic(this, &UInv_SpaceInv::ShowEquip);

	Button_Cons->OnClicked.AddDynamic(this, &UInv_SpaceInv::ShowCons);

	ShowEquip();
	Grid_Mate->SetParent(this);
	Grid_Work->SetParent(this);
	Grid_Equip->SetParent(this);
	Grid_Cons->SetParent(this);
}

void UInv_SpaceInv::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInv_SpaceInv::ShowMate()
{
	SetActiveGrid(Grid_Mate, Button_Mate);
}

void UInv_SpaceInv::ShowWork()
{
	SetActiveGrid(Grid_Work, Button_Work);
}

void UInv_SpaceInv::ShowEquip()
{
	SetActiveGrid(Grid_Equip, Button_Equip);
}

void UInv_SpaceInv::ShowCons()
{
	SetActiveGrid(Grid_Cons, Button_Cons);
}

void UInv_SpaceInv::DisableButton(UButton* button)
{
	Button_Mate->SetIsEnabled(true);
	Button_Work->SetIsEnabled(true);
	Button_Equip->SetIsEnabled(true);
	Button_Cons->SetIsEnabled(true);
	button->SetIsEnabled(false);
}

void UInv_SpaceInv::SetActiveGrid(UInv_GridInv*Grid, UButton* button)
{
	DisableButton(button);
	Switcher->SetActiveWidget(Grid);
}

FInv_SlotAvailabilityResult UInv_SpaceInv::HasRoomForItem(UPickUpComponent* imc) const
{
	return FInv_SlotAvailabilityResult();
}
