// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Inv_MessageHUD.h"
#include "Components/TextBlock.h"
void UInv_MessageHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Text_Message->SetText(FText::GetEmpty());
	MessageHide();
}

void UInv_MessageHUD::SetMessage(const FText& text) {
	Text_Message->SetText(text);

	if (!bIsMessageActive)
	{
		MessageShow();
	}
	bIsMessageActive = true;
	GetWorld()->GetTimerManager().SetTimer(MessageTimer, [this]() {
		MessageHide();
		bIsMessageActive = false;

		}, MessageLifetime, false);
};