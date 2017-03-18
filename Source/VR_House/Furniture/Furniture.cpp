// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "Furniture.h"




AFurniture::AFurniture()
{
	PrimaryActorTick.bCanEverTick = true;

	m_furnitureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Furniture Mesh"));
	m_furnitureMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_furnitureMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}
