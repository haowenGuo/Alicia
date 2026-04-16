// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/PickUpComponent.h"

// Sets default values for this component's properties
UPickUpComponent::UPickUpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPickUpComponent::InitializeComponent()
{
    Super::InitializeComponent();
    
}

void UPickUpComponent::BeginPlay()
{
    Super::BeginPlay();
    InitItem();
}

UInv_Item* UPickUpComponent::InitItem()
{

    // 检查类引用是否有效（避免空指针）
    if (!ItemClass)
    {
        UE_LOG(LogTemp, Error, TEXT("ItemClass 未在细节面板中设置！"));
        return nullptr;
    }

    // 创建 UInv_Item 实例（使用选中的类）
    // 参数1：Outer（所有者，通常是当前对象或 GetWorld()）
    // 参数2：类（从 ItemClass 获取）
    UInv_Item* NewItem = NewObject<UInv_Item>(this, ItemClass);

    if (NewItem)
    {
        UE_LOG(LogTemp, Display, TEXT("成功创建实例：%s"), *NewItem->GetName());
        // 可在此处初始化实例属性（如设置数量、状态等）
    }
    item = NewItem;

    return NewItem;
    
}


