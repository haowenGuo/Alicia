// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/AliciaGameInstance.h"
#include <Kismet/GameplayStatics.h>

void UAliciaGameInstance::ReStartGame()
{
	UGameplayStatics::OpenLevel(this, *GetWorld()->GetName(), false);
	
}
