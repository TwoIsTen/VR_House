// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "HousePlayer.h"
#include "MotionControllerComponent.h"

// Sets default values
AHousePlayer::AHousePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	m_leftController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_leftController->Hand = EControllerHand::Left;

	m_rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	m_rightController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_rightController->Hand = EControllerHand::Right;
}

// Called when the game starts or when spawned
void AHousePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHousePlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AHousePlayer::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);

}

