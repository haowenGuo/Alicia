// Fill out your copyright notice in the Description page of Project Settings.


#include "Inv_Widgets/Utils/Inv_GridUtils.h"

int32 UInv_GridUtils::GetIndexFromPosition(const FIntPoint& position, const int32 columns)
{
	return position.X + position.Y * columns;
}
