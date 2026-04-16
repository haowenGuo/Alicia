// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include"PickUp/PickUpComponent.h"
#include "InvManagerComponent.generated.h"

class UInv_Base;
class UInv_Item;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInvItemChange, UInv_Item* ,Item,int32, num);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInv);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ,Blueprintable)
class INV_HAOWENGUO_API UInvManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInvManagerComponent();

	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UPickUpComponent* puc, int32 StackCount);

	UFUNCTION(Server, Reliable)
	void Server_AddStacksItem(UPickUpComponent* puc, int32 StackCount, int32 Remainder);

	UPROPERTY(EditAnywhere, Category = "Inv")
	TSubclassOf<UInv_Base> Inv_MenuClass;

	UPROPERTY()
	TObjectPtr<UInv_Base> Inv_Menu;

	TWeakObjectPtr<APlayerController> OwningController;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool isOpenInv=false;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void ConstructInv();

	UFUNCTION(BlueprintCallable, Category = "Inv")
	virtual void ChangeInvOpenClose();

	UPROPERTY()
	FInvItemChange OnItemAdded;

	UPROPERTY()
	FInvItemChange OnItemRemoved;

	FNoRoomInInv NoRoomInInv;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundBase> PickUpSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USoundBase> DropSound;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Inv")
	void TryAddItem(UPickUpComponent* pickupcomponent);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Inv")
	void TryRemoveItem(UInv_Item* Inv_Item,int32 num);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Inv")
	void TryDropItem(UInv_Item* Inv_Item, int32 num);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Inv")
	void ConsumeItem(UInv_Item* Inv_Item);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Inv")
	void EquipItem(UInv_Item* Inv_Item);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Inv")
	void UnEquipItem(UInv_Item* Inv_Item);

	virtual void InvOpen();

	virtual void InvClose();
};
