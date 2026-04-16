// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/HighUpStaticMeshComponent.h"

void UHighUpStaticMeshComponent::HightLight_Implementation()
{
	SetOverlayMaterial(hightlightMaterial);
	
}

void UHighUpStaticMeshComponent::UnHightLight_Implementation()
{
	SetOverlayMaterial(nullptr);
}
