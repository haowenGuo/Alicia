// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "HighLightface.h"
#include "HighUpStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class INV_HAOWENGUO_API UHighUpStaticMeshComponent : public UStaticMeshComponent,public IHighLightface
{
	GENERATED_BODY()

public:
	virtual void HightLight_Implementation() override;

	virtual void UnHightLight_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface>hightlightMaterial;
};
