// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AliciaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ALICIA_API UAliciaGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ReStartGame();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float GameStartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WorldTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WorldYear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WorldMonth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WorldDay;


};
