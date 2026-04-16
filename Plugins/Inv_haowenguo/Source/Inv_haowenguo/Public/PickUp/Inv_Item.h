// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Types.h>
#include "Inv_Item.generated.h"


UCLASS(BlueprintType, Blueprintable)
class INV_HAOWENGUO_API UInv_Item : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString ItemName;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inv")
	TSubclassOf<class AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInv_ItemCategory ItemCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInv_EquipCategory EquipCategory= EInv_EquipCategory::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bStackable=false;

};
