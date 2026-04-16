// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <InvManager/InvManagerComponent.h>
#include "Inv_Utils.generated.h"


/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UInv_Utils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "INV")
	static UInvManagerComponent* GetInvManagerComponent(const APlayerController* PlayerController);
};
