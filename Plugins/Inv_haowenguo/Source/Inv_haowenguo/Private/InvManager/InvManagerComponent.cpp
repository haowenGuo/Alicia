// Fill out your copyright notice in the Description page of Project Settings.


#include "InvManager/InvManagerComponent.h"
#include "Inv_Widgets/Inv_Base.h"
#include <Inv_Widgets/Space/Inv_SpaceInv.h>
#include <Kismet/GameplayStatics.h>
#include <InvInterfaces/EquippableInterface.h>
#include <Inv_Widgets/Space/Inv_EquipGridInv.h>
// Sets default values for this component's properties
UInvManagerComponent::UInvManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



// Called when the game starts
void UInvManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ConstructInv();
}


// Called every frame
void UInvManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInvManagerComponent::ConstructInv()
{
	OwningController = Cast<APlayerController>(GetOwner());
	checkf(OwningController.IsValid(), TEXT("OwningController is null"));
	if (!OwningController->IsLocalController())return;

	Inv_Menu = CreateWidget<UInv_Base>(OwningController.Get(),Inv_MenuClass);
	UInv_SpaceInv* Inv_SpaceMenu = Cast<UInv_SpaceInv>(Inv_Menu);
	if (Inv_SpaceMenu) {
		Inv_SpaceMenu->SetInvManagerComponent(this);
		Inv_SpaceMenu->AddToViewport();
		//Inv_SpaceMenu->SetVisibility(ESlateVisibility::Collapsed);
	}
	InvClose();
}

void UInvManagerComponent::ChangeInvOpenClose()
{
	if (isOpenInv) {
		InvClose();
	}
	else {
		InvOpen();
	}
	isOpenInv = !isOpenInv;
}


void UInvManagerComponent::TryAddItem(UPickUpComponent* pickupcomponent)
{
	UE_LOG(LogTemp, Display, TEXT("try Add a item"));
	if (!pickupcomponent)return;
	if (PickUpSound) {
		AController* OwnerController = Cast<AController>(GetOwner());
		APawn* ControlledPawn;
		if (OwnerController)
		{
			// 获取控制器控制的 Pawn
			ControlledPawn = OwnerController->GetPawn();
			if (ControlledPawn) {
				UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, ControlledPawn->GetActorLocation());
			}

		}

	}
	OnItemAdded.Broadcast(pickupcomponent->item,1);
	/*
	FInv_SlotAvailabilityResult Result = Inv_Menu->HasRoomForItem(pickupcomponent);
	if (Result.TotalRoomToFill == 0) {
		NoRoomInInv.Broadcast();
		return;
	}
	if (Result.Item.IsValid() && Result.bStackable) {
		Server_AddStacksItem(pickupcomponent,Result.TotalRoomToFill,Result.Remainder);
	}
	else if (Result.TotalRoomToFill>0) {
		Server_AddNewItem(pickupcomponent, Result.bStackable?Result.TotalRoomToFill:0);
	}*/
}

void UInvManagerComponent::TryRemoveItem(UInv_Item* Inv_Item, int32 num)
{
	if (!Inv_Item)return;
	UE_LOG(LogTemp, Display, TEXT("try remove a item"));
	OnItemRemoved.Broadcast(Inv_Item, num);

	
}

void UInvManagerComponent::TryDropItem(UInv_Item* Inv_Item, int32 num)
{
	if (!Inv_Item)return;
	UE_LOG(LogTemp, Display, TEXT("try drop a item"));
	if (Inv_Item->ItemCategory == EInv_ItemCategory::Equippable)
	{
		UnEquipItem(Inv_Item);
	}
	OnItemRemoved.Broadcast(Inv_Item,num);
	AController* OwnerController = Cast<AController>(GetOwner());
	APawn* ControlledPawn;
	if (OwnerController)
	{
		// 获取控制器控制的 Pawn
		ControlledPawn = OwnerController->GetPawn();
		FVector LOC = ControlledPawn->GetActorLocation() + ControlledPawn->GetActorForwardVector() * 50.f;
		FRotator RO = ControlledPawn->GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor<class AActor>(Inv_Item->ActorClass, LOC, RO);
	}
}

void UInvManagerComponent::ConsumeItem(UInv_Item* Inv_Item)
{
	if (!Inv_Item)return;
	AController* OwnerController = Cast<AController>(GetOwner());
	OnItemRemoved.Broadcast(Inv_Item, 1);
	APawn* ControlledPawn;
	if (OwnerController)
	{
		// 获取控制器控制的 Pawn
		ControlledPawn = OwnerController->GetPawn();
		FVector LOC = ControlledPawn->GetActorLocation();
		FRotator RO = ControlledPawn->GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		SpawnParams.Owner = Cast<AActor>(ControlledPawn);
		AActor* actor=GetWorld()->SpawnActor<class AActor>(Inv_Item->ActorClass, LOC, RO, SpawnParams);
		if (actor) {
			actor->Destroy();
		}
		
	}
}

void UInvManagerComponent::EquipItem(UInv_Item* Inv_Item)
{
	if (!Inv_Item)return;
	AController* OwnerController = Cast<AController>(GetOwner());
	UInv_SpaceInv* SpaceInv = Cast<UInv_SpaceInv>(Inv_Menu);
	if (!SpaceInv)return;
	UInv_EquipGridInv* EquipGridInv = Cast<UInv_EquipGridInv>(SpaceInv->Grid_Equip);
	if (!EquipGridInv)return;
	EquipGridInv->Equip(Inv_Item);


	APawn* ControlledPawn;
	if (OwnerController)
	{
		// 获取控制器控制的 Pawn
		ControlledPawn = OwnerController->GetPawn();
		IEquippableInterface* equipment = Cast<IEquippableInterface>(ControlledPawn);
		FVector LOC = ControlledPawn->GetActorLocation() + ControlledPawn->GetActorForwardVector() * 2000.f;;
		FRotator RO = ControlledPawn->GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		SpawnParams.Owner = Cast<AActor>(ControlledPawn);
		

		if (equipment) {
			AActor* actor = GetWorld()->SpawnActor<class AActor>(Inv_Item->ActorClass, LOC, RO, SpawnParams);
			switch (Inv_Item->EquipCategory)
			{
			case(EInv_EquipCategory::RightHandWeapon): 
				if (equipment->EquipRightWeapon(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::LeftHandWeapon):
				if (equipment->EquipLeftWeapon(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::Head):
				if (equipment->EquipHead(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::Hand):
				if (equipment->EquipHand(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::UpperBody):
				if (equipment->EquipUpperBody(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::LowerBody):
				if (equipment->EquipLowerBody(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::Arm):
				if (equipment->EquipArm(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::Foot):
				if (equipment->EquipFoot(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::Ring):
				if (equipment->EquipRing(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			case(EInv_EquipCategory::Neck):
				if (equipment->EquipNeck(actor) == 0) {
					if (actor) {
						actor->Destroy();
					}
				}
				break;
			}
		}
	}
}

void UInvManagerComponent::UnEquipItem(UInv_Item* Inv_Item)
{
	if (!Inv_Item)return;
	UInv_SpaceInv* SpaceInv = Cast<UInv_SpaceInv>(Inv_Menu);
	if (!SpaceInv)return;
	UInv_EquipGridInv* EquipGridInv = Cast<UInv_EquipGridInv>(SpaceInv->Grid_Equip);
	if (!EquipGridInv)return;
	EquipGridInv->UnEquip(Inv_Item);

	AController* OwnerController = Cast<AController>(GetOwner());
	APawn* ControlledPawn;
	if (OwnerController)
	{
		// 获取控制器控制的 Pawn
		ControlledPawn = OwnerController->GetPawn();
		IEquippableInterface* equipment = Cast<IEquippableInterface>(ControlledPawn);

		if (equipment) {
			switch (Inv_Item->EquipCategory)
			{
			case(EInv_EquipCategory::RightHandWeapon):
				equipment->UnEquipRightWeapon();
				break;
			case(EInv_EquipCategory::LeftHandWeapon):
				equipment->UnEquipLeftWeapon();
				break;
			case(EInv_EquipCategory::Head):
				equipment->UnEquipHead();
				break;
			case(EInv_EquipCategory::Hand):
				equipment->UnEquipHand();
				break;
			case(EInv_EquipCategory::UpperBody):
				equipment->UnEquipUpperBody();
				break;
			case(EInv_EquipCategory::LowerBody):
				equipment->UnEquipLowerBody();
				break;
			case(EInv_EquipCategory::Arm):
				equipment->UnEquipArm();
				break;
			case(EInv_EquipCategory::Foot):
				equipment->UnEquipFoot();
				break;
			case(EInv_EquipCategory::Ring):
				equipment->UnEquipRing();
				break;
			case(EInv_EquipCategory::Neck):
				equipment->UnEquipNeck();
				break;
			}
		}
	}
}

void UInvManagerComponent::Server_AddNewItem_Implementation(UPickUpComponent* puc, int32 StackCount)
{

}



void UInvManagerComponent::Server_AddStacksItem_Implementation(UPickUpComponent* puc, int32 StackCount, int32 Remainder)
{

}

void UInvManagerComponent::InvOpen()
{
	if (Inv_Menu)
	{
		Inv_Menu->SetVisibility(ESlateVisibility::Visible);
		//Inv_Menu->AddToViewport();
	}
	if (!OwningController.IsValid()) {
		return;
	}
	FInputModeGameAndUI InputMode;
	//UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),0.01f);
	//FInputModeUIOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(true);
}

void UInvManagerComponent::InvClose()
{
	if (Inv_Menu)
	{
		Inv_Menu->SetVisibility(ESlateVisibility::Collapsed);
		//Inv_Menu->RemoveFromParent();
	}
	if (!OwningController.IsValid()) {
		return;
	}
	//UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	FInputModeGameOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(false);
}

