// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AliciaWidgetController.h"

void UAliciaWidgetController::SetAliciaWidgetControllerParams(FAliciaWidgetControllerParams params)
{
	PlayerController = params.PlayerController;
	PlayerState = params.PlayerState;
	AbilitySystemComponent = params.AbilitySystemComponent;
	AttributeSet = params.AttributeSet;
}

void UAliciaWidgetController::BroadcastInitialValues()
{
}

void UAliciaWidgetController::BindCallbacksToDependencies()
{
}
