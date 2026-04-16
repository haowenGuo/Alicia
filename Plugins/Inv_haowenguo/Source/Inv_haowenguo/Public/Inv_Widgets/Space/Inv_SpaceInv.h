// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inv_Widgets/Inv_Base.h"
#include"Inv_Widgets/Space/Inv_GridInv.h"
#include"Inv_Widgets/Space/Inv_EquipGridInv.h"
#include <Components/WidgetSwitcher.h>
#include "Inv_SpaceInv.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UInv_SpaceInv : public UInv_Base
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct()override;

	TObjectPtr<class UInvManagerComponent>InvManagerComponent;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher>Switcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_EquipGridInv>Grid_Equip;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_GridInv>Grid_Cons;


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_GridInv>Grid_Mate;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_GridInv>Grid_Work;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>Button_Equip;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>Button_Cons;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>Button_Mate;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton>Button_Work;

	UFUNCTION()
	void ShowEquip();


	UFUNCTION()
	void ShowCons();

	UFUNCTION()
	void ShowMate();

	UFUNCTION()
	void ShowWork();

	UFUNCTION()
	void SetInvManagerComponent(UInvManagerComponent* imc) 
	{ 
		InvManagerComponent = imc;
		if (Grid_Equip) {
			Grid_Equip->SetInvManagerComponent(InvManagerComponent);
		}
		if (Grid_Cons) {
			Grid_Cons->SetInvManagerComponent(InvManagerComponent);
		}
		if (Grid_Mate) {
			Grid_Mate->SetInvManagerComponent(InvManagerComponent);
		}
		if (Grid_Work) {
			Grid_Work->SetInvManagerComponent(InvManagerComponent);
		}
	};


	void DisableButton(UButton* button);
	void SetActiveGrid(UInv_GridInv* Grid,UButton* button);

	virtual FInv_SlotAvailabilityResult HasRoomForItem(UPickUpComponent* imc)const override;

};
