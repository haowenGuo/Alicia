// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WidgetController/OverlayAliciaWidgetController.h"
#include "AliciaHUD.generated.h"


struct  FAliciaWidgetControllerParams;
/**
 * 
 */
UCLASS()
class ALICIA_API AAliciaHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UAliciaUserWidget> OverlayWidget;
	
	UOverlayAliciaWidgetController* GetOverlayWidgetController(FAliciaWidgetControllerParams& Params);

	void InitOverlay(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as);

	UFUNCTION(BlueprintCallable)
	void InitHUD();
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Menu;

	UPROPERTY()
	TObjectPtr<UUserWidget>GameMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> SaveMenuClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UUserWidget>SaveMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>OpenMenuClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UUserWidget>OpenMenu;

	UPROPERTY(BlueprintReadWrite)
	TArray<UUserWidget*>WidgetStack;

	UFUNCTION(BlueprintCallable)
	void OpenGameMenu();

	UFUNCTION(BlueprintCallable)
	void CloseGameMenu();

	UFUNCTION(BlueprintCallable)
	void OpenOpenMenu();

	UFUNCTION(BlueprintCallable)
	void CloseOpenMenu();

	UFUNCTION(BlueprintCallable)
	void OpenSaveMenu();

	UFUNCTION(BlueprintCallable)
	void CloseSaveMenu();

	UFUNCTION(BlueprintCallable)
	void CloseAllMenu();

	UFUNCTION(BlueprintCallable)
	bool IsStackEmpty();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetStackFirst();

	UFUNCTION(BlueprintCallable)
	void PopStackLast();

	UFUNCTION(BlueprintCallable)
	void EseAction();

	UPROPERTY(EditAnywhere)
	APlayerController* OwningController;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAliciaUserWidget> OverlayWidgetClass;



	UPROPERTY()
	TObjectPtr<UOverlayAliciaWidgetController>OverlayAliciaWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAliciaWidgetController> OverlayAliciaWidgetControllerClass;
};
