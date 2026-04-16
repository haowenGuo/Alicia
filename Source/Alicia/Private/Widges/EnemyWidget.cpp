// Fill out your copyright notice in the Description page of Project Settings.


#include "Widges/EnemyWidget.h"
#include "Components/ProgressBar.h"
#include "Widges/EnemyWidget.h"

void UEnemyWidget::SetHealth(float percentage)
{
	HealthBar->SetPercent(percentage);
}

void UEnemyWidget::SetStamina(float percentage)
{
	StaminaBar->SetPercent(percentage);
}
