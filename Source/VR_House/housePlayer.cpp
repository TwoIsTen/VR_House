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

	InputComp->BindAxis("MoveForward", this, &AHousePlayer::MoveForward);
	InputComp->BindAxis("MoveRight", this, &AHousePlayer::MoveRight);

	InputComp->BindAxis("LookUp", this, &AHousePlayer::LookUp);
	InputComp->BindAxis("LookRight", this, &AHousePlayer::LookRight);

	InputComp->BindAction("Debug_KeyboardControl", EInputEvent::IE_Pressed, this, &AHousePlayer::SetControllByKeyBoard);

}

void AHousePlayer::MoveForward(float distance)
{
	if (distance != 0.0f)
	{
		AddActorWorldOffset(GetActorForwardVector()* 5.0f * distance);
	}
}

void AHousePlayer::MoveRight(float distance)
{
	if (distance != 0.0f)
	{
		AddActorWorldOffset(GetActorRightVector() * 5.0f * distance);
	}
}

void AHousePlayer::LookUp(float angle)
{
	AddControllerPitchInput(angle * 50.0f * GetWorld()->GetDeltaSeconds());
}

void AHousePlayer::LookRight(float angle)
{
	AddControllerYawInput(angle * 50.0f * GetWorld()->GetDeltaSeconds());
}

void AHousePlayer::SetControllByKeyBoard()
{
	m_leftController->SetRelativeLocationAndRotation(FVector(10.0f, -10.0f, 0.0f), FRotator::ZeroRotator);
	m_rightController->SetRelativeLocationAndRotation(FVector(10.0f, 10.0f, 0.0f), FRotator::ZeroRotator);
}
