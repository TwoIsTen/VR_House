// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "HousePlayer.h"
#include "MotionControllerComponent.h"

// Sets default values
AHousePlayer::AHousePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	m_cameraComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	m_leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	m_leftController->AttachToComponent(m_cameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_leftController->Hand = EControllerHand::Left;

	m_rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	m_rightController->AttachToComponent(m_cameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_rightController->Hand = EControllerHand::Right;
	

	m_leftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Hand Mesh"));
	m_leftHandMesh->AttachToComponent(m_leftController, FAttachmentTransformRules::KeepRelativeTransform);

	m_rightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Hand Mesh"));
	m_rightHandMesh->AttachToComponent(m_rightController, FAttachmentTransformRules::KeepRelativeTransform);

	m_leftTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Left Trace Start Point"));
	m_leftTraceStart->AttachToComponent(m_leftController, FAttachmentTransformRules::KeepRelativeTransform);

	m_rightTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Right Trace Start Point"));
	m_rightTraceStart->AttachToComponent(m_rightController, FAttachmentTransformRules::KeepRelativeTransform);
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

	InputComp->BindAction("LeftTrigger",EInputEvent::IE_Pressed, this, &AHousePlayer::UseLeftTrigger);

	InputComp->BindAction("Debug_KeyboardControl", EInputEvent::IE_Pressed, this, &AHousePlayer::Debug_SetControllByKeyBoard);

}

void AHousePlayer::MoveForward(float distance)
{
	if (distance != 0.0f)
	{
		m_cameraComponent->AddLocalOffset(FVector(200.0 * distance * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f));
	}
}

void AHousePlayer::MoveRight(float distance)
{
	if (distance != 0.0f)
	{
		m_cameraComponent->AddLocalOffset(FVector(0.0f, 200.0 * distance * GetWorld()->GetDeltaSeconds(), 0.0f));
	}
}

void AHousePlayer::LookUp(float angle)
{
	m_cameraComponent->AddLocalRotation(FRotator(angle * 75.0f * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f));
}

void AHousePlayer::LookRight(float angle)
{
	m_cameraComponent->AddWorldRotation(FRotator(0.0f, angle * 75.0f * GetWorld()->GetDeltaSeconds(), 0.0f));
}

void AHousePlayer::Debug_SetControllByKeyBoard()
{
	m_leftController->SetRelativeLocationAndRotation(FVector(100.0f, -10.0f, 0.0f), FRotator::ZeroRotator);
	m_rightController->SetRelativeLocationAndRotation(FVector(100.0f, 10.0f, 0.0f), FRotator::ZeroRotator);
}

FVector AHousePlayer::GetCameraLocation()
{
	check(m_cameraComponent);
	return m_cameraComponent->GetComponentLocation();
}

void AHousePlayer::UseLeftTrigger()
{
	PRINT_ON_SCREEN("Use Left Trigger");

	FHitResult hit;
	FVector start = m_leftTraceStart->GetComponentLocation();
	FVector end = start + m_leftController->GetForwardVector() * 1500.0f;
	FCollisionQueryParams param;

	if (ActorLineTraceSingle(hit, start, end, ECollisionChannel::ECC_Visibility, param))
	{
		hit.GetActor()->AddActorWorldOffset(FVector(0.0f, 0.0f, 10.0f));
		PRINT_ON_SCREEN("Hit Actor : %s", *hit.GetActor()->GetName());
	}
}
