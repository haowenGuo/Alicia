// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AliciaHUD.h"
#include"UI/AliciaUserWidget.h"
#include <Kismet/GameplayStatics.h>
UOverlayAliciaWidgetController* AAliciaHUD::GetOverlayWidgetController(FAliciaWidgetControllerParams& Params)
{
	if (OverlayAliciaWidgetController == nullptr)
	{
		OverlayAliciaWidgetController = NewObject<UOverlayAliciaWidgetController>(this, OverlayAliciaWidgetControllerClass);
		OverlayAliciaWidgetController->SetAliciaWidgetControllerParams(Params);
		return OverlayAliciaWidgetController;
	}
	return OverlayAliciaWidgetController;
}
void AAliciaHUD::InitOverlay(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as)
{
	check(OverlayAliciaWidgetControllerClass);
	check(OverlayWidgetClass);

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UAliciaUserWidget>(Widget);

	FAliciaWidgetControllerParams Params(pc, ps, asc, as);
	UOverlayAliciaWidgetController * oawc = GetOverlayWidgetController(Params);
	OverlayWidget->SetWidgetController(oawc);
	oawc->BroadcastInitialValues();
	Widget->AddToViewport(0);

	InitHUD();
	
}
void AAliciaHUD::InitHUD()
{
	OwningController = Cast<APlayerController>(GetOwningPlayerController());

	GameMenu = CreateWidget<UUserWidget>(GetWorld(), Menu);
	OpenMenu = CreateWidget<UUserWidget>(GetWorld(), OpenMenuClass);
	SaveMenu = CreateWidget<UUserWidget>(GetWorld(), SaveMenuClass);


	OpenMenu->AddToViewport(2);
	OpenMenu->SetVisibility(ESlateVisibility::Collapsed);

	SaveMenu->AddToViewport(3);
	SaveMenu->SetVisibility(ESlateVisibility::Collapsed);

	GameMenu->AddToViewport(1);
	GameMenu->SetVisibility(ESlateVisibility::Collapsed);
}
void AAliciaHUD::CloseGameMenu()
{
	if (!OwningController)return;
	if (IsStackEmpty())return;
	if (GameMenu->IsVisible())
	{
		if (WidgetStack[WidgetStack.Num() - 1] != GameMenu) return;
		GameMenu->SetVisibility(ESlateVisibility::Collapsed);
		WidgetStack.Pop();
		//UGameplayStatics::SetGamePaused(GetWorld(), false);
		if (IsStackEmpty())
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
			FInputModeGameOnly InputMode;
			OwningController->SetShowMouseCursor(false);
			OwningController->SetInputMode(InputMode);
		}

	}


}
void AAliciaHUD::OpenGameMenu()
{
	if (!OwningController) return;
	if (!IsStackEmpty())
	{
		if (WidgetStack[WidgetStack.Num() - 1] == GameMenu) return;
	}
	
	GameMenu->SetVisibility(ESlateVisibility::Visible);
	WidgetStack.Add(GameMenu);
	OwningController->SetShowMouseCursor(true);
	FInputModeGameAndUI InputMode;
	//UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01f);
	//FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(GameMenu->TakeWidget()); // 设置焦点到指定的Widget
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 鼠标不锁定
	OwningController->SetInputMode(InputMode);
}
void AAliciaHUD::OpenOpenMenu()
{
	for (int i = WidgetStack.Num() - 1; i >=0; --i)
	{
		WidgetStack[i]->SetVisibility(ESlateVisibility::Collapsed);
		WidgetStack.Pop();
	}
	WidgetStack.Add(OpenMenu);
	WidgetStack[0] -> SetVisibility(ESlateVisibility::Visible);
	FInputModeUIOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01f);
}
void AAliciaHUD::CloseOpenMenu()
{

	for (int i = WidgetStack.Num() - 1; i >= 0; --i)
	{
		WidgetStack[i]->SetVisibility(ESlateVisibility::Collapsed);
		WidgetStack.Pop();
	}

	FInputModeGameOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}
void AAliciaHUD::OpenSaveMenu()
{
	if (!OwningController) return;
	if (!IsStackEmpty()) {
		if (WidgetStack[WidgetStack.Num() - 1] == SaveMenu) return;
	}
	
	WidgetStack.Add(SaveMenu);
	WidgetStack[WidgetStack.Num()-1]->SetVisibility(ESlateVisibility::Visible);

	OwningController->SetShowMouseCursor(true);
	FInputModeGameAndUI InputMode;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01f);
	OwningController->SetInputMode(InputMode);
}
void AAliciaHUD::CloseSaveMenu()
{
	if (!OwningController)return;
	if (IsStackEmpty())return;
	if (WidgetStack[WidgetStack.Num() - 1] != SaveMenu)return;
	SaveMenu->SetVisibility(ESlateVisibility::Collapsed);
	WidgetStack.Pop();
	//UGameplayStatics::SetGamePaused(GetWorld(), false);
		
	if (WidgetStack.Num() == 0)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
		FInputModeGameOnly InputMode;
		OwningController->SetShowMouseCursor(false);
		OwningController->SetInputMode(InputMode);
	}
}
void AAliciaHUD::CloseAllMenu()
{
	for (int i = WidgetStack.Num() - 1; i >= 0; --i)
	{
		WidgetStack[i]->SetVisibility(ESlateVisibility::Collapsed);
		WidgetStack.Pop();
	}
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	FInputModeGameOnly InputMode;
	OwningController->SetShowMouseCursor(false);
	OwningController->SetInputMode(InputMode);
}
bool AAliciaHUD::IsStackEmpty()
{
	if (WidgetStack.Num() <= 0)	return true;
	return false;
}
UUserWidget* AAliciaHUD::GetStackFirst()
{
	if (!IsStackEmpty())return WidgetStack[0];
	return nullptr;
}
void AAliciaHUD::PopStackLast()
{
	if (!IsStackEmpty())
	{
		UUserWidget* wid = WidgetStack[WidgetStack.Num() - 1];
		if (wid == GameMenu)
		{
			CloseGameMenu();
		}
		else if (wid == OpenMenu)
		{
			CloseOpenMenu();
		}
		else if (wid == SaveMenu)
		{
			CloseSaveMenu();
		}
	}
}
void AAliciaHUD::EseAction()
{
	if (!IsStackEmpty())
	{
		for (int i = WidgetStack.Num() - 1; i >= 0; --i)
		{
			UUserWidget* wid = WidgetStack[i];
			if (wid == GameMenu)
			{
				CloseGameMenu();
			}
			else if (wid == OpenMenu)
			{
				return;
			}
			else if (wid == SaveMenu)
			{
				CloseSaveMenu();
			}
		}
	}

}
void AAliciaHUD::BeginPlay()
{
	Super::BeginPlay();

}
