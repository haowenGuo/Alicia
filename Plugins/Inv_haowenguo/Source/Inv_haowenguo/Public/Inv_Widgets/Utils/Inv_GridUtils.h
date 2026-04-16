// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Inv_GridUtils.generated.h"

/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UInv_GridUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static int32 GetIndexFromPosition(const FIntPoint& position, const int32 columns);
};
