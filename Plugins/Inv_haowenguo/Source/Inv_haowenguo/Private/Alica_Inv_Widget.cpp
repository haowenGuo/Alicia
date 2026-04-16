// Fill out your copyright notice in the Description page of Project Settings.


#include "Alica_Inv_Widget.h"
#include <InvManager/InvManagerComponent.h>
#include <InvManager/Utils/Inv_Utils.h>
#include <HUD/Inv_MessageHUD.h>
/*
void UAlica_Inv_Widget::ShowPickUpMessage(const FString& Message)
{
}

void UAlica_Inv_Widget::HidePickUpMessage()
{
}*/

void UAlica_Inv_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UInvManagerComponent* imc = UInv_Utils::GetInvManagerComponent(GetOwningPlayer());
	if (IsValid(imc))
	{
		imc->NoRoomInInv.AddDynamic(this, &UAlica_Inv_Widget::OnNoRoom);
	}
}

void UAlica_Inv_Widget::OnNoRoom()
{
	if (!IsValid(MessageInfo))return;
	MessageInfo->SetMessage(FText::FromString("No Room"));
}
