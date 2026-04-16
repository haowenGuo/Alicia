// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickUp/Inv_Item.h"
#include "Inv_GridSlot.generated.h"
class UImage;
class UTextBlock;
class UInv_GridInv;
/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UInv_GridSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage>Image_GridSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage>Image_border;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInv_Item> item;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInv_GridInv>Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (BindWidget))
	TObjectPtr<UTextBlock>Number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	int32 StackNumber=0;

	void SetIndex(int32 i) { Index = i; }

	void AddStackNumber(int32 num);

	void SubtackNumber(int32 num);

	void ShowBorder();

	void CloseBorder();

	void InitItem(UInv_Item* Invitem);

	UFUNCTION(BlueprintCallable)
	void SetParent(UInv_GridInv* widget);
};
