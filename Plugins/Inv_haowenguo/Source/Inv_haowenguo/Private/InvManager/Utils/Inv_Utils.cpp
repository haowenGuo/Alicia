// Fill out your copyright notice in the Description page of Project Settings.


#include "InvManager/Utils/Inv_Utils.h"

UInvManagerComponent* UInv_Utils::GetInvManagerComponent(const APlayerController* PlayerController)
{
	if(!IsValid(PlayerController))
	return nullptr;

	UInvManagerComponent* imc = PlayerController->FindComponentByClass<UInvManagerComponent>();
	return imc;
}
