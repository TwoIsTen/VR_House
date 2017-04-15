// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "HousePlayer.h"
#include "Furniture/Furniture.h"
#include "MotionControllerComponent.h"

//--------------------------------------------------------------------------------
AHousePlayer::AHousePlayer()
//pointers
	: m_selectedFurniture(nullptr)
	//bools
	, m_isLeftTriggerPressing(false)
	, m_isRightTriggerPressing(false)
	, m_isLeftGripPressing(false)
	, m_isRightGripPressing(false)
	//FVectors
	, m_leftControlLastPos(0.0f)
	, m_rightControlLastPos(0.0f)
	//FRotator
	, m_leftControlLastRot(0.0f)
	, m_rightControlLastRot(0.0f)
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
	m_leftTraceStart->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_rightTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Right Trace Start Point"));
	m_rightTraceStart->AttachToComponent(m_rightController, FAttachmentTransformRules::KeepRelativeTransform);
	m_rightTraceStart->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_leftTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Left Trace End Point"));
	m_leftTraceEnd->AttachToComponent(m_leftController, FAttachmentTransformRules::KeepRelativeTransform);
	m_leftTraceEnd->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_rightTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Right Trace End Point"));
	m_rightTraceEnd->AttachToComponent(m_rightController, FAttachmentTransformRules::KeepRelativeTransform);
	m_rightTraceEnd->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_leftLaser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Trace Lazer"));
	m_leftLaser->AttachToComponent(m_leftController, FAttachmentTransformRules::KeepRelativeTransform);
	m_leftLaser->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_rightLaser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Trace Lazer"));
	m_rightLaser->AttachToComponent(m_rightController, FAttachmentTransformRules::KeepRelativeTransform);
	m_rightLaser->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
}

//--------------------------------------------------------------------------------
void AHousePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	m_leftLaser->SetVisibility(false);
	m_rightLaser->SetVisibility(false);

	m_leftControlLastPos = m_leftController->GetComponentLocation();
	m_rightControlLastPos = m_rightController->GetComponentLocation();

	m_leftControlLastRot = m_leftController->GetComponentRotation();
	m_rightControlLastRot = m_rightController->GetComponentRotation();
}

//--------------------------------------------------------------------------------
void AHousePlayer::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	//variables may used by tick
	FVector LeftControlCurrentPos = m_leftController->GetComponentLocation();
	FVector RightControlCurrentPos = m_rightController->GetComponentLocation();
	FVector LeftControlDeltaPos = LeftControlCurrentPos - m_leftControlLastPos;
	FVector RightControlDeltaPos = RightControlCurrentPos - m_rightControlLastPos;

	FRotator LeftControlCurrentRot = m_leftController->GetComponentRotation();
	FRotator RightControlCurrentRot = m_rightController->GetComponentRotation();
	FRotator LeftControlDeltaRot = LeftControlCurrentRot - m_leftControlLastRot;
	FRotator RightControlDeltaRot = RightControlCurrentRot - m_rightControlLastRot;

	if (m_isRightGripPressing && nullptr != m_selectedFurniture)
	{
		float times = 1.0f;
		if (m_isRightTriggerPressing)
		{
			times *= 5.0f;
		}
		else if (m_isLeftTriggerPressing)
		{
			times /= 5.0f;
		}

		FVector tempPos = m_selectedFurniture->GetActorLocation();
		tempPos += RightControlDeltaPos * times;
		if (tempPos.Z < 0.0f)
		{
			tempPos.Z = 0.0f;
		}
		m_selectedFurniture->SetActorLocation(tempPos);
	}

	if (m_isLeftGripPressing && nullptr != m_selectedFurniture)
	{
		float times = 1.0f;
		if (m_isRightTriggerPressing)
		{
			times *= 5.0f;
		}
		else if (m_isLeftTriggerPressing)
		{
			times /= 5.0f;
		}

		FRotator tempRot = LeftControlDeltaRot * times;
		tempRot.Pitch = 0.0f;
		tempRot.Roll = 0.0f;
		m_selectedFurniture->AddActorWorldRotation(tempRot);
	}

	//update variables need update per frame
	m_leftControlLastPos = LeftControlCurrentPos;
	m_rightControlLastPos = RightControlCurrentPos;
	m_leftControlLastRot = LeftControlCurrentRot;
	m_rightControlLastRot = RightControlCurrentRot;
}

//--------------------------------------------------------------------------------
void AHousePlayer::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);

	InputComp->BindAxis("MoveForward", this, &AHousePlayer::MoveForward);
	InputComp->BindAxis("MoveRight", this, &AHousePlayer::MoveRight);

	InputComp->BindAxis("LookUp", this, &AHousePlayer::LookUp);
	InputComp->BindAxis("LookRight", this, &AHousePlayer::LookRight);

	InputComp->BindAction("LeftTrigger", EInputEvent::IE_Pressed, this, &AHousePlayer::StartUseLeftTrigger);
	InputComp->BindAction("LeftTrigger", EInputEvent::IE_Released, this, &AHousePlayer::EndUseLeftTrigger);

	InputComp->BindAction("RightTrigger", EInputEvent::IE_Pressed, this, &AHousePlayer::StartUseRightTrigger);
	InputComp->BindAction("RightTrigger", EInputEvent::IE_Released, this, &AHousePlayer::EndUseRightTrigger);

	InputComp->BindAction("RightGrip", EInputEvent::IE_Pressed, this, &AHousePlayer::StartUseRightGrip);
	InputComp->BindAction("RightGrip", EInputEvent::IE_Released, this, &AHousePlayer::EndUseRightGrip);

	InputComp->BindAction("LeftGrip", EInputEvent::IE_Pressed, this, &AHousePlayer::StartUseLeftGrip);
	InputComp->BindAction("LeftGrip", EInputEvent::IE_Released, this, &AHousePlayer::EndUseLeftGrip);

	InputComp->BindAction("Debug_KeyboardControl", EInputEvent::IE_Pressed, this, &AHousePlayer::Debug_SetControllByKeyBoard);

}

//--------------------------------------------------------------------------------
void AHousePlayer::MoveForward(float distance)
{
	if (distance != 0.0f)
	{
		m_cameraComponent->AddLocalOffset(FVector(200.0 * distance * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f));
	}
}

//--------------------------------------------------------------------------------
void AHousePlayer::MoveRight(float distance)
{
	if (distance != 0.0f)
	{
		m_cameraComponent->AddLocalOffset(FVector(0.0f, 200.0 * distance * GetWorld()->GetDeltaSeconds(), 0.0f));
	}
}

//--------------------------------------------------------------------------------
void AHousePlayer::LookUp(float angle)
{
	m_cameraComponent->AddLocalRotation(FRotator(angle * 75.0f * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f));
}

//--------------------------------------------------------------------------------
void AHousePlayer::LookRight(float angle)
{
	m_cameraComponent->AddWorldRotation(FRotator(0.0f, angle * 75.0f * GetWorld()->GetDeltaSeconds(), 0.0f));
}

//--------------------------------------------------------------------------------
void AHousePlayer::Debug_SetControllByKeyBoard()
{
	m_leftController->SetRelativeLocationAndRotation(FVector(100.0f, -10.0f, 0.0f), FRotator::ZeroRotator);
	m_rightController->SetRelativeLocationAndRotation(FVector(100.0f, 10.0f, 0.0f), FRotator::ZeroRotator);
}

//--------------------------------------------------------------------------------
FVector AHousePlayer::GetCameraLocation()
{
	check(m_cameraComponent);
	return m_cameraComponent->GetComponentLocation();
}

//--------------------------------------------------------------------------------
void AHousePlayer::StartUseLeftTrigger()
{
	m_isLeftTriggerPressing = true;

	if (m_isLeftGripPressing || m_isRightGripPressing) return;

	m_leftLaser->SetVisibility(true);
}

//--------------------------------------------------------------------------------
void AHousePlayer::EndUseLeftTrigger()
{
	m_isLeftTriggerPressing = false;

	if (m_leftLaser->bVisible)
	{
		m_leftLaser->SetVisibility(false);

		FVector start = m_leftTraceStart->GetComponentLocation();
		FVector end = m_leftTraceEnd->GetComponentLocation();

		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.bTraceAsyncScene = true;
		RV_TraceParams.bReturnPhysicalMaterial = false;

		//Re-initialize hit info
		FHitResult RV_Hit(ForceInit);

		//call GetWorld() from within an actor extending class
		GetWorld()->LineTraceSingleByChannel(
			RV_Hit,        //result
			start,    //start
			end, //end
			ECollisionChannel::ECC_Visibility, //collision channel
			RV_TraceParams
		);

		if (RV_Hit.bBlockingHit)
		{
			m_selectedFurniture = Cast<AFurniture>(RV_Hit.GetActor());
			if (m_selectedFurniture)
			{
				PRINT_ON_SCREEN("Hit Furniture %s", *m_selectedFurniture->GetName());
			}
			else
			{
				PRINT_ON_SCREEN("Hit something but Furniture");
			}
		}
		else
		{
			m_selectedFurniture = nullptr;
		}
	}
}

//--------------------------------------------------------------------------------
void AHousePlayer::StartUseRightTrigger()
{
	m_isRightTriggerPressing = true;

	if (m_isLeftGripPressing || m_isRightGripPressing) return;
	
	m_rightLaser->SetVisibility(true);
}

//--------------------------------------------------------------------------------
void AHousePlayer::EndUseRightTrigger()
{
	m_isRightTriggerPressing = false;

	if (m_rightLaser->bVisible)
	{
		m_rightLaser->SetVisibility(false);

		FVector start = m_rightTraceStart->GetComponentLocation();
		FVector end = m_rightTraceEnd->GetComponentLocation();

		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.bTraceAsyncScene = true;
		RV_TraceParams.bReturnPhysicalMaterial = false;

		//Re-initialize hit info
		FHitResult RV_Hit(ForceInit);

		//call GetWorld() from within an actor extending class
		GetWorld()->LineTraceSingleByChannel(
			RV_Hit,        //result
			start,    //start
			end, //end
			ECollisionChannel::ECC_Visibility, //collision channel
			RV_TraceParams
		);

		if (RV_Hit.bBlockingHit)
		{
			m_selectedFurniture = Cast<AFurniture>(RV_Hit.GetActor());
			if (m_selectedFurniture)
			{
				PRINT_ON_SCREEN("Hit Furniture %s", *m_selectedFurniture->GetName());
			}
			else
			{
				PRINT_ON_SCREEN("Hit something but Furniture");
			}
		}
		else
		{
			m_selectedFurniture = nullptr;
		}
	}
}

void AHousePlayer::StartUseLeftGrip()
{
	m_isLeftGripPressing = true;
}

void AHousePlayer::EndUseLeftGrip()
{
	m_isLeftGripPressing = false;
}

void AHousePlayer::StartUseRightGrip()
{
	m_isRightGripPressing = true;
}

void AHousePlayer::EndUseRightGrip()
{
	m_isRightGripPressing = false;
}

//--------------------------------------------------------------------------------