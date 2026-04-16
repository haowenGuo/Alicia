// Copyright Epic Games, Inc. All Rights Reserved.

#include "AliciaGameMode.h"
#include "AliciaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>

#include"Enemies/Enemy.h"

AAliciaGameMode::AAliciaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void AAliciaGameMode::GameInit()
{
	check(Aosa);
	check(Monst0);
	check(DarkKnight);
	check(ShadowKnight);
	check(PatrolPoint);
	TArray<AActor*>Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PatrolPoint, Points);
	int32 count = 0;
	for (count = 0; count < EnemyNum; count++)
	{
		int index = FMath::RandRange(0, Points.Num() - 1);
		FVector LOC = Points[index]->GetActorLocation();
		LOC.X += FMath::RandRange(-50000.f, 50000.f);
		LOC.Y += FMath::RandRange(-50000.f, 50000.f);
		LOC.Z = 10000.f;
		FRotator RO = Points[index]->GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		int EnemyId = FMath::RandRange(0, 20);
		AEnemy* enemy = nullptr;
		if (EnemyId < 8)
		{
			enemy = GetWorld()->SpawnActor<AEnemy>(Monst0, LOC, RO, SpawnParams);
		}
		else if (EnemyId < 15)
		{
			enemy = GetWorld()->SpawnActor<AEnemy>(DarkKnight, LOC, RO, SpawnParams);
		}
		else if (EnemyId < 18)
		{
			enemy = GetWorld()->SpawnActor<AEnemy>(Aosa, LOC, RO, SpawnParams);
		}
		else
		{
			enemy = GetWorld()->SpawnActor<AEnemy>(ShadowKnight, LOC, RO, SpawnParams);
		}

		for (int i = 0; i < PatrolNum; i++)
		{
			int PatrolId = FMath::RandRange(0, Points.Num() - 1);
			enemy->patrolpoints.Add(Points[PatrolId]);
		}



	}
}
void AAliciaGameMode::BeginPlay()
{

	/*
	for (int i = 0; i < Points.Num(); i++)
	{
		for (int t = 0; t < EnemyNum / Points.Num(); t++)
		{
			FVector LOC = Points[i]->GetActorLocation();
			FRotator RO = Points[i]->GetActorRotation();
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			GetWorld()->SpawnActor<AEnemy>(DarkKnight, LOC, RO, SpawnParams);
		}

	}*/
}
void AAliciaGameMode::ReStartGame()
{
	UGameplayStatics::OpenLevel(this, *GetWorld()->GetName(), false);
	
}