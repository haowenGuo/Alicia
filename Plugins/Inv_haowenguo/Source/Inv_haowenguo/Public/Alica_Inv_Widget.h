// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Alica_Inv_Widget.generated.h"
class UInv_MessageHUD;
/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UAlica_Inv_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized()override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Inv")
	void ShowPickUpMessage(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = "Inv")
	void HidePickUpMessage();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_MessageHUD> MessageInfo;

	UFUNCTION()
	void OnNoRoom();
};
