// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"Types.h"
#include "Inv_Base.generated.h"

class UPickUpComponent;
/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UInv_Base : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual FInv_SlotAvailabilityResult HasRoomForItem(UPickUpComponent* imc)const 
	{
		return FInv_SlotAvailabilityResult();
	};
};
