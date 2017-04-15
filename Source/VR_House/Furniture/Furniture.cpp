// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "Furniture.h"




AFurniture::AFurniture()
{
	PrimaryActorTick.bCanEverTick = true;

	m_root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	m_root->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_root->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

void AFurniture::BeginPlay()
{
	Super::BeginPlay();
}

void AFurniture::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
