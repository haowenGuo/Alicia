// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"PickUp/Inv_Item.h"
#include "PickUpComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ,Blueprintable)
class INV_HAOWENGUO_API UPickUpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickUpComponent();

	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
protected:
	
public:	
	UInv_Item* InitItem();
	UPROPERTY(EditAnywhere, Category = "Inv")
	FString PickUpMessage=FString("Press E Pick Up");

	UPROPERTY(EditAnywhere, Category = "Inv")
	TSubclassOf<UInv_Item> ItemClass; // 现在可在细节面板选择 UInv_Item 或其蓝图类

	UPROPERTY(EditAnywhere,Category = "Inv")
	TObjectPtr<UInv_Item> item;


	FString GetPickUpMessage()const { return PickUpMessage; }
};
