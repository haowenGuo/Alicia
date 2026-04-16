// Fill out your copyright notice in the Description page of Project Settings.


#include "Inv_Widgets/Space/Inv_GridSlot.h"
#include"Components/TextBlock.h"
#include "Components/Image.h"
#include <Inv_Widgets/Space/Inv_GridInv.h>

void UInv_GridSlot::AddStackNumber(int32 num)
{
    StackNumber += num;
    Number->SetText(FText::FromString(FString::FromInt(StackNumber)));
}

void UInv_GridSlot::SubtackNumber(int32 num)
{
    if (num <= 0)return;
    StackNumber -= num;
    Number->SetText(FText::FromString(FString::FromInt(StackNumber)));
}

void UInv_GridSlot::ShowBorder()
{
    Image_border->SetVisibility(ESlateVisibility::Visible);
}

void UInv_GridSlot::CloseBorder()
{
    Image_border->SetVisibility(ESlateVisibility::Collapsed);
}

void UInv_GridSlot::InitItem(UInv_Item* Invitem)
{
	item = Invitem;
    if (Image_GridSlot)
    {
        // 创建 Slate 画笔（FSlateBrush）
        FSlateBrush ImageBrush;
        ImageBrush.SetResourceObject(item->ItemIcon); // 关联纹理资源
        ImageBrush.DrawAs = ESlateBrushDrawType::Image; // 绘制类型为图片

        // 设置 UImage 的画笔
        Image_GridSlot->SetBrush(ImageBrush);
        Image_border->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UInv_GridSlot::SetParent(UInv_GridInv* widget)
{
    Parent = widget;
}
