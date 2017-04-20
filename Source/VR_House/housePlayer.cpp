// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "HousePlayer.h"
#include "Furniture/Furniture.h"
#include "MotionControllerComponent.h"
#include "WidgetComponent.h"
#include "GlobalParameter.h"
#include "Kismet/KismetStringLibrary.h"

//--------------------------------------------------------------------------------
AHousePlayer::AHousePlayer()
//pointers
	: m_selectedFurniture(nullptr)
	//bools
	, m_isLeftTriggerPressing(false)
	, m_isRightTriggerPressing(false)
	, m_isLeftGripPressing(false)
	, m_isRightGripPressing(false)
	//floats
	, m_times(1.0f)
	, m_menuScaleX(0.0f)
	, m_menuScaleY(0.0f)
	, m_scaleProgress(0.0f)
	, m_menuScaleSpeedX(0.0f)
	, m_menuScaleSpeedY(0.0f)
	, m_selectScaleX(0.0f)
	, m_selectScaleY(0.0f)
	, m_selectScaleSpeedX(0.0f)
	, m_selectScaleSpeedY(0.0f)
	, m_selectScaleProgress(0.0f)
	//FVectors
	, m_leftControlLastPos(0.0f)
	, m_rightControlLastPos(0.0f)
	, m_leftControlCurrentPos(0.0f)
	, m_rightControlCurrentPos(0.0f)
	, m_leftControlDeltaPos(0.0f)
	, m_rightControlDeltaPos(0.0f)
	//FRotator
	, m_leftControlLastRot(0.0f)
	, m_rightControlLastRot(0.0f)
	, m_leftControlCurrentRot(0.0f)
	, m_rightControlCurrentRot(0.0f)
	, m_leftControlDeltaRot(0.0f)
	, RightControlDeltaRot(0.0f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root Component"));
	m_cameraRoot->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	m_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	m_cameraComponent->AttachToComponent(m_cameraRoot, FAttachmentTransformRules::KeepRelativeTransform);

	m_leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	m_leftController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_leftController->Hand = EControllerHand::Left;

	m_rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	m_rightController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	m_rightController->Hand = EControllerHand::Right;


	m_leftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Hand Mesh"));
	m_leftHandMesh->AttachToComponent(m_leftController, FAttachmentTransformRules::KeepRelativeTransform);

	m_rightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Hand Mesh"));
	m_rightHandMesh->AttachToComponent(m_rightController, FAttachmentTransformRules::KeepRelativeTransform);

	m_leftTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Left Trace Start Point"));
	m_leftTraceStart->AttachToComponent(m_leftHandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	m_leftTraceStart->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_rightTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Right Trace Start Point"));
	m_rightTraceStart->AttachToComponent(m_rightHandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	m_rightTraceStart->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_leftTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Left Trace End Point"));
	m_leftTraceEnd->AttachToComponent(m_leftHandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	m_leftTraceEnd->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_rightTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Right Trace End Point"));
	m_rightTraceEnd->AttachToComponent(m_rightHandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	m_rightTraceEnd->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_leftLaser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Trace Lazer"));
	m_leftLaser->AttachToComponent(m_leftHandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	m_leftLaser->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_rightLaser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Trace Lazer"));
	m_rightLaser->AttachToComponent(m_rightHandMesh, FAttachmentTransformRules::KeepRelativeTransform);
	m_rightLaser->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	m_menuAttachNode = CreateDefaultSubobject<USceneComponent>(TEXT("Menu AttachNode"));

	m_menuBackGround = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu BackGround"));
	m_menuBackGround->SetPivot(FVector2D(0.5f, 1.0f));
	m_menuBackGround->AttachToComponent(m_menuAttachNode, FAttachmentTransformRules::KeepRelativeTransform);
	m_menuBackGround->SetVisibility(false);
	m_menuBackGround->SetBlendMode(EWidgetBlendMode::Transparent);
	m_menuBackGround->SetDrawSize(FVector2D(1.0f, 1.0f));
	m_menuBackGround->SetRelativeScale3D(FVector(0.1f, 0.0f, 0.0f));
	m_menuBackGround->SetRelativeLocation(FVector(0.0f));
	m_menuBackGround->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	m_menuBackGround->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_selectFrame = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu Select Frame"));
	m_selectFrame->SetPivot(FVector2D(0.5f, 1.0f));
	m_selectFrame->AttachToComponent(m_menuAttachNode, FAttachmentTransformRules::KeepRelativeTransform);
	m_selectFrame->SetVisibility(false);
	m_selectFrame->SetBlendMode(EWidgetBlendMode::Transparent);
	m_selectFrame->SetDrawSize(FVector2D(1.0f, 1.0f));
	m_selectFrame->SetRelativeScale3D(FVector(0.1f, 0.0f, 0.0f));
	m_selectFrame->SetRelativeLocation(FVector(-0.1f, 0.0f, 0.0f));
	m_selectFrame->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	m_selectFrame->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
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

	m_playerState = EPlayerState::Free;

	m_menuBackGround->SetWidgetClass(AGlobalParameterReader::GetParameter()->MenuBackgroundWidget);
	m_menuBackGround->InitWidget();

	m_selectFrame->SetWidgetClass(AGlobalParameterReader::GetParameter()->SelectFrameWidget);
	m_selectFrame->InitWidget();
}

//--------------------------------------------------------------------------------
void AHousePlayer::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	//variables may used by tick
	m_leftControlCurrentPos = m_leftController->GetComponentLocation();
	m_rightControlCurrentPos = m_rightController->GetComponentLocation();
	m_leftControlDeltaPos = m_leftControlCurrentPos - m_leftControlLastPos;
	m_rightControlDeltaPos = m_rightControlCurrentPos - m_rightControlLastPos;

	m_leftControlCurrentRot = m_leftController->GetComponentRotation();
	m_rightControlCurrentRot = m_rightController->GetComponentRotation();
	m_leftControlDeltaRot = m_leftControlCurrentRot - m_leftControlLastRot;
	RightControlDeltaRot = m_rightControlCurrentRot - m_rightControlLastRot;

	switch (m_playerState)
	{
	case EPlayerState::Free :
		break;
	case EPlayerState::Laser :
		break;
	case EPlayerState::OnMainMenu :
		break;
	case EPlayerState::SelectFurniture :
	{
		TickState_SelectFurniture();
		break;
	}
	case EPlayerState::MoveFurniture :
	{
		TickState_MoveFurniture();
		break;
	}
	case EPlayerState::RotateFurniture:
	{
		TickState_RotateFurniture();
		break; 
	}
	//case EPlayerState:: :
	//	break;
	//case EPlayerState:: :
	//	break;
	//case EPlayerState:: :
	//	break;
	default:
		UE_LOG(LogHouse, Warning, TEXT("Invaild player state"));
		break;
	}


	UpdateMenuBackGround(DeltaTime);
	UpdateSelectFrame(DeltaTime);

	//update variables need update per frame
	m_leftControlLastPos = m_leftControlCurrentPos;
	m_rightControlLastPos = m_rightControlCurrentPos;
	m_leftControlLastRot = m_leftControlCurrentRot;
	m_rightControlLastRot = m_rightControlCurrentRot;
}

void AHousePlayer::TickState_SelectFurniture()
{
}

void AHousePlayer::TickState_RotateFurniture()
{
	FRotator tempRot = m_leftControlDeltaRot * m_times;
	tempRot.Pitch = 0.0f;
	tempRot.Roll = 0.0f;

	m_selectedFurniture->AddActorWorldRotation(tempRot, true);
}

void AHousePlayer::TickState_MoveFurniture()
{
	m_rightControlDeltaPos *= m_times;
	FHitResult result;
	m_selectedFurniture->AddActorWorldOffset(m_rightControlDeltaPos, true);
	if (result.IsValidBlockingHit())
	{
		PRINT_ON_SCREEN(FColor::Red, "Hit Something: %s", *result.GetActor()->GetName());
	}
}

UWidgetComponent* AHousePlayer::GenerateWidgetComponent(FName& name)
{
	UWidgetComponent* comp;
	comp = NewObject<UWidgetComponent>(this, name);
	comp->RegisterComponent();
	comp->SetPivot(FVector2D(0.5f, 1.0f));
	comp->AttachToComponent(m_menuAttachNode, FAttachmentTransformRules::KeepRelativeTransform);
	comp->SetVisibility(false);
	comp->SetBlendMode(EWidgetBlendMode::Transparent);
	comp->SetRelativeScale3D(FVector(0.1f));
	comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	return comp;
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

	InputComp->BindAction("LeftMenuButton", EInputEvent::IE_Pressed, this, &AHousePlayer::StartUseLeftMenu);
	InputComp->BindAction("RightMenuButton", EInputEvent::IE_Pressed, this, &AHousePlayer::StartUseRightMenu);


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
	m_leftController->AttachToComponent(m_cameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_leftController->SetRelativeLocationAndRotation(FVector(69.281929f, -40.000183f, -21.0f), FRotator(0.0f, -30.0f, 0.0f));
	m_rightController->AttachToComponent(m_cameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_rightController->SetRelativeLocationAndRotation(FVector(69.281929f, 40.000183f, -21.0f), FRotator(0.0f, 30.0f, 0.0f));
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

	switch (m_playerState)
	{
	case EPlayerState::Free:
		m_leftLaser->SetVisibility(true);
		m_playerState = EPlayerState::Laser;
		break;
	case EPlayerState::Laser:
		break;
	case EPlayerState::SelectFurniture:
		m_leftLaser->SetVisibility(true);
		if (m_selectedFurniture)
		{
			m_selectedFurniture->MoveFinished();
		}
		m_selectedFurniture = nullptr;
		m_playerState = EPlayerState::Laser;
		break;
	case EPlayerState::MoveFurniture:
		m_times *= 5.0f;
		break;
	case EPlayerState::RotateFurniture:
		m_times *= 5.0f;
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		UE_LOG(LogHouse, Warning, TEXT("Invaild player state"));
		break;
	}
}

//--------------------------------------------------------------------------------
void AHousePlayer::EndUseLeftTrigger()
{
	m_isLeftTriggerPressing = false;

	switch (m_playerState)
	{
	case EPlayerState::Free:
		break;
	case EPlayerState::Laser:
		StopLaser(true);
		break;
	case EPlayerState::SelectFurniture:
		break;
	case EPlayerState::MoveFurniture:
		m_times /= 5.0f;
		break;
	case EPlayerState::RotateFurniture:
		m_times /= 5.0f;
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		break;
	}
}

void AHousePlayer::StopLaser(bool isLeft)
{
	UStaticMeshComponent* laser = isLeft ? m_leftLaser : m_rightLaser;
	USceneComponent* TraceStart = isLeft ? m_leftTraceStart : m_rightTraceStart;
	USceneComponent* TraceEnd = isLeft ? m_leftTraceEnd : m_rightTraceEnd;

	if (laser->bVisible)
	{
		laser->SetVisibility(false);

		FVector start = TraceStart->GetComponentLocation();
		FVector end = TraceEnd->GetComponentLocation();

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
				m_selectedFurniture->PrepareToMove();
				m_playerState = EPlayerState::SelectFurniture;
			}
			else
			{
				m_playerState = EPlayerState::Free;
			}
		}
	}//else do nothing
}

//--------------------------------------------------------------------------------
void AHousePlayer::StartUseRightTrigger()
{
	m_isRightTriggerPressing = true;

	switch (m_playerState)
	{
	case EPlayerState::Free:
		m_rightLaser->SetVisibility(true);
		m_playerState = EPlayerState::Laser;
		break;
	case EPlayerState::Laser:
		break;
	case EPlayerState::SelectFurniture:
		m_rightLaser->SetVisibility(true);
		if (m_selectedFurniture)
		{
			m_selectedFurniture->MoveFinished();
		}
		m_selectedFurniture = nullptr;
		m_playerState = EPlayerState::Laser;
		break;
	case EPlayerState::MoveFurniture:
		m_times /= 5.0f;
		break;
	case EPlayerState::RotateFurniture:
		m_times /= 5.0f;
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		UE_LOG(LogHouse, Warning, TEXT("Invaild player state"));
		break;
	}
}

//--------------------------------------------------------------------------------
void AHousePlayer::EndUseRightTrigger()
{
	m_isRightTriggerPressing = false;

	switch (m_playerState)
	{
	case EPlayerState::Free:
		break;
	case EPlayerState::Laser:
		StopLaser(false);
		break;
	case EPlayerState::SelectFurniture:
		break;
	case EPlayerState::MoveFurniture:
		m_times *= 5.0f;
		break;
	case EPlayerState::RotateFurniture:
		m_times *= 5.0f;
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		break;
	}
}

void AHousePlayer::StartUseLeftGrip()
{
	m_isLeftGripPressing = true;

	switch (m_playerState)
	{
	case EPlayerState::Free:
		break;
	case EPlayerState::Laser:
		break;
	case EPlayerState::SelectFurniture:
		m_playerState = EPlayerState::MoveFurniture;
		break;
	case EPlayerState::MoveFurniture:
		break;
	case EPlayerState::RotateFurniture:
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		break;
	}
}

void AHousePlayer::EndUseLeftGrip()
{
	m_isLeftGripPressing = false;

	switch (m_playerState)
	{
	case EPlayerState::Free:
		break;
	case EPlayerState::Laser:
		break;
	case EPlayerState::SelectFurniture:
		break;
	case EPlayerState::MoveFurniture:
		m_playerState = EPlayerState::SelectFurniture;
		break;
	case EPlayerState::RotateFurniture:
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		break;
	}
}

void AHousePlayer::StartUseRightGrip()
{
	m_isRightGripPressing = true;

	switch (m_playerState)
	{
	case EPlayerState::Free:
		break;
	case EPlayerState::Laser:
		break;
	case EPlayerState::SelectFurniture:
		m_playerState = EPlayerState::RotateFurniture;
		break;
	case EPlayerState::MoveFurniture:
		break;
	case EPlayerState::RotateFurniture:
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		break;
	}
}

void AHousePlayer::EndUseRightGrip()
{
	m_isRightGripPressing = false;

	switch (m_playerState)
	{
	case EPlayerState::Free:
		break;
	case EPlayerState::Laser:
		break;
	case EPlayerState::SelectFurniture:
		break;
	case EPlayerState::MoveFurniture:
		break;
	case EPlayerState::RotateFurniture:
		m_playerState = EPlayerState::SelectFurniture;
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		break;
	}
}

void AHousePlayer::StartUseLeftMenu()
{
	switch (m_playerState)
	{
	case EPlayerState::Free:
		ShowMenu(EMenuType::MainMenu, true);
		m_playerState = EPlayerState::OnMainMenu;
		break;
	case EPlayerState::Laser:
		break;
	case EPlayerState::SelectFurniture:
		break;
	case EPlayerState::MoveFurniture:
		break;
	case EPlayerState::RotateFurniture:
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		break;
	}
}

void AHousePlayer::StartUseRightMenu()
{
	switch (m_playerState)
	{
	case EPlayerState::Free:
		ShowMenu(EMenuType::MainMenu, false);
		m_playerState = EPlayerState::OnMainMenu;
		break;
	case EPlayerState::Laser:
		break;
	case EPlayerState::SelectFurniture:
		break;
	case EPlayerState::MoveFurniture:
		break;
	case EPlayerState::RotateFurniture:
		break;
	case EPlayerState::OnMainMenu:
		break;
	default:
		break;
	}
}

void AHousePlayer::ShowMenu(EMenuType::Type type, bool isLeft)
{
	UStaticMeshComponent* hand = isLeft ? m_leftHandMesh : m_rightHandMesh;

	m_menuAttachNode->AttachToComponent(hand, FAttachmentTransformRules::KeepRelativeTransform);
	m_menuAttachNode->SetRelativeLocation(FVector(10.0f, 0.0f, 0.0f));

	switch (type)
	{
	case EMenuType::MainMenu:
		{
			m_menuContents.Empty();
			AGlobalParameterReader::GetParameter()->MainMenuData->GetAllRows<FMenuInfo>(FString("Menu Info"), m_menuContents);
			MakeMenu();
		}
		break;
	default:
		break;
	}


	TArray<USceneComponent*> childern;
	m_menuAttachNode->GetChildrenComponents(true, childern);
	for (int i = 0, n = childern.Num(); i < n; ++i)
	{
		childern[i]->SetVisibility(true);
	}
}

void AHousePlayer::MakeMenu()
{
	int num = m_menuContents.Num();
	m_menuScaleX = 0.0f;
	m_menuScaleY = 0.0f;
	float baseY = 0.0f;
	for (int i = num - 1; i >= 0; --i)
	{
		FString tstr = FString::Printf(TEXT("Menu Contents %d"), i);
		FName name = UKismetStringLibrary::Conv_StringToName(tstr);
		UWidgetComponent* comp = GenerateWidgetComponent(name);
		comp->SetWidgetClass(m_menuContents[i]->Widget);
		comp->InitWidget();
		comp->SetDrawSize(m_menuContents[i]->DrawSize);
		m_menuScaleX = FMath::Max(m_menuScaleX, m_menuContents[i]->DrawSize.X);
		m_menuScaleY += m_menuContents[i]->DrawSize.Y;
		comp->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		comp->SetRelativeLocation(FVector(-0.2f, 0.0f, baseY));
		baseY += m_menuContents[i]->DrawSize.Y * 0.1;
	}
	baseY -= m_menuContents[0]->DrawSize.Y * 0.1;
	m_selectScaleX = m_menuContents[0]->DrawSize.X * 0.1;
	m_selectScaleY = m_menuContents[0]->DrawSize.Y * 0.1;
	m_selectFrame->SetRelativeLocation(FVector(-0.1f, 0.0f, baseY));
	m_menuScaleX /= 10.0f;
	m_menuScaleY /= 10.0f;

	m_menuAttachNode->SetRelativeLocation(FVector(10.0f, 0.0f, -baseY));
}

void AHousePlayer::UpdateMenuBackGround(float DeltaTime)
{
	FVector scale = m_menuBackGround->GetRelativeTransform().GetScale3D();
	if (scale.Y != m_menuScaleX || scale.Z != m_menuScaleY)
	{
		if (m_scaleProgress == 0.0f)
		{
			m_menuScaleSpeedX = (m_menuScaleX - scale.Y) / m_scaleTime;
			m_menuScaleSpeedY = (m_menuScaleY - scale.Z) / m_scaleTime;
		}

		m_scaleProgress += DeltaTime / m_scaleTime;
		scale.Y = FMath::Min(m_menuScaleX, scale.Y + m_menuScaleSpeedX * DeltaTime);
		scale.Z = FMath::Min(m_menuScaleY, scale.Z + m_menuScaleSpeedY * DeltaTime);
		m_menuBackGround->SetRelativeScale3D(scale);

		if (m_scaleProgress >= 1.0f)
		{
			m_scaleProgress = 0.0f;
		}
	}
}

void AHousePlayer::UpdateSelectFrame(float DeltaTime)
{
	FVector scale = m_selectFrame->GetRelativeTransform().GetScale3D();
	if (scale.Y != m_selectScaleX || scale.Z != m_selectScaleY)
	{
		if (m_selectScaleProgress == 0.0f)
		{
			m_selectScaleSpeedX = (m_selectScaleX - scale.Y) / m_scaleTime;
			m_selectScaleSpeedY = (m_selectScaleY - scale.Z) / m_scaleTime;
		}

		m_selectScaleProgress += DeltaTime / m_scaleTime;
		scale.Y = scale.Y + m_selectScaleX * DeltaTime;
		scale.Z = scale.Z + m_selectScaleY * DeltaTime;
		if (m_selectScaleProgress >= 1.0f)
		{
			scale.Y = m_selectScaleX;
			scale.Z = m_selectScaleY;
			m_selectScaleProgress = 0.0f;
		}
		m_selectFrame->SetRelativeScale3D(scale);
	}
}

//--------------------------------------------------------------------------------