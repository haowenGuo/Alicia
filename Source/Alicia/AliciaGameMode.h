// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AliciaGameMode.generated.h"
class AEnemy;
UCLASS(minimalapi)
class AAliciaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAliciaGameMode();

	UFUNCTION(BlueprintCallable)
	virtual void GameInit();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void ReStartGame();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AEnemy> Aosa;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemy> Monst0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemy> DarkKnight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemy> ShadowKnight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PatrolPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemyNum=200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PotionNum=1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Diffculty=2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PatrolNum=3.f;
};



