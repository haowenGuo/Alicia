// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolListWidget.generated.h"
class UInv_Item;
/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UToolListWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inv")
	TObjectPtr<UInv_Item>item;

	UFUNCTION(BlueprintCallable)
	void SetItem(UInv_Item* Inv_Item);
};
