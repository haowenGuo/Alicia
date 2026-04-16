// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"Types.h"
#include "Inv_GridInv.generated.h"

class UInv_GridSlot;
class UCanvasPanel;
class UInv_Item;
class UInv_SpaceInv;
/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UInv_GridInv : public UUserWidget
{
	GENERATED_BODY()
	
public:

	EInv_ItemCategory GetCategory() const{
		return InvCategory;
	}
	virtual void NativeOnInitialized()override;

	virtual void NativeConstruct()override;
	void ConstructGrid();

	UFUNCTION(BlueprintCallable)
	void AddGridSlot(UInv_Item* item,int32 num);

	UFUNCTION(BlueprintCallable)
	void RemoveGridSlot(UInv_Item* item, int32 num);

	UFUNCTION(BlueprintCallable)
	void RefreshGridSlot();

	UFUNCTION(BlueprintCallable)
	void SetParent(UInv_SpaceInv* widget);

	UFUNCTION()
	void SetInvManagerComponent(UInvManagerComponent* imc) { InvManagerComponent = imc; };

	TObjectPtr<class UInvManagerComponent>InvManagerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Inv")
	EInv_ItemCategory InvCategory;

	UPROPERTY()
	TArray<TObjectPtr<UInv_GridSlot>> GridSlots;

	UPROPERTY(EditAnywhere, Category = "Inv")
	TSubclassOf<UInv_GridSlot>GridSlotClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel>GridCanvasPanel;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInv_SpaceInv>Parent;

	UPROPERTY(EditAnywhere, Category = "Inv")
	int32 GridRows;

	UPROPERTY(EditAnywhere, Category = "Inv")
	int32 GridColumns;

	UPROPERTY(EditAnywhere, Category = "Inv")
	float SlotSize;

	UPROPERTY(EditAnywhere, Category = "Inv")
	int32 SlotNumber=0;


};
