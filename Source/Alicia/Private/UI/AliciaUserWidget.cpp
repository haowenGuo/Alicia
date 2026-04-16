// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AliciaUserWidget.h"

void UAliciaUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
