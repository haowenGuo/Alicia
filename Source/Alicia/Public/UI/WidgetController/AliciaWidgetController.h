// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AliciaWidgetController.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;
USTRUCT(BlueprintType)
struct FAliciaWidgetControllerParams
{
	GENERATED_BODY()


	FAliciaWidgetControllerParams(){}
	FAliciaWidgetControllerParams(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as):
		PlayerController(pc), PlayerState(ps), AbilitySystemComponent(asc), AttributeSet(as){};
		
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerState>PlayerState;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet;
};

UCLASS()
class ALICIA_API UAliciaWidgetController : public UObject
{
	GENERATED_BODY()

	
public:
	UAliciaWidgetController() {};

	UFUNCTION(BlueprintCallable)
	void SetAliciaWidgetControllerParams(FAliciaWidgetControllerParams params) ;

	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependencies();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
