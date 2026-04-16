// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_MessageHUD.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UInv_MessageHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized()override;
	UFUNCTION(BlueprintImplementableEvent, Category = "Inv")
	void MessageShow();

	UFUNCTION(BlueprintImplementableEvent, Category = "Inv")
	void MessageHide();

	void SetMessage(const FText& text);
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock>Text_Message;

	UPROPERTY(EditAnywhere, Category = "Inv")
	float MessageLifetime{ 3.f };
	
	FTimerHandle MessageTimer;
	bool bIsMessageActive{ false };



};
