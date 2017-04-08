// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "MoveAxis.h"
#include "housePlayer.h"

AHousePlayer* AMoveAxis::m_mainPlayer = nullptr;

// Sets default values
AMoveAxis::AMoveAxis()
	: m_active(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(m_rootComponent);

	m_axisRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Axis Root Component"));
	m_axisRootComponent->AttachToComponent(m_rootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	m_xArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("X Axis"));
	m_xArrow->AttachToComponent(m_axisRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_xArrow->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	m_xArrow->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	m_xArrow->SetRenderCustomDepth(true);
	m_xArrow->SetCustomDepthStencilValue(1);
	m_xArrow->SetHiddenInGame(false);

	m_yArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Y Axis"));
	m_yArrow->AttachToComponent(m_axisRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_yArrow->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	m_yArrow->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	m_yArrow->SetArrowColor_New(FLinearColor::Yellow);
	m_yArrow->SetRenderCustomDepth(true);
	m_yArrow->SetCustomDepthStencilValue(0);
	m_yArrow->SetHiddenInGame(false);

	m_zArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Z Axis"));
	m_zArrow->AttachToComponent(m_axisRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_zArrow->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	m_zArrow->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	m_zArrow->SetArrowColor_New(FLinearColor::Blue);
	m_zArrow->SetRenderCustomDepth(true);
	m_zArrow->SetCustomDepthStencilValue(255);
	m_zArrow->SetHiddenInGame(false);

	//SetMoveAxisEnable(false);
}

// Called when the game starts or when spawned
void AMoveAxis::BeginPlay()
{
	Super::BeginPlay();
	
	m_mainPlayer = Cast<AHousePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void AMoveAxis::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	m_mainPlayer = nullptr;
}

// Called every frame
void AMoveAxis::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (m_active)
	{
		if (m_mainPlayer == nullptr || m_mainPlayer->GetName() == FString("None"))
		{
			m_mainPlayer = Cast<AHousePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
			return;
		}
		float dist = (GetActorLocation() - m_mainPlayer->GetCameraLocation()).Size();
		if (dist > 100.0f)
		{
			dist /= 200.0f;
		}
		else
		{
			dist = 0.5f;
		}
		m_xArrow->SetRelativeScale3D(FVector(dist));
		//m_xArrow->MarkRenderStateDirty();
		m_yArrow->ArrowSize = dist;
		m_yArrow->MarkRenderStateDirty();
		m_zArrow->ArrowSize = dist;
		m_zArrow->MarkRenderStateDirty();
	}
}

void AMoveAxis::SetMoveAxisEnable(bool bEnable)
{
	if (m_active != bEnable)
	{
		m_active = bEnable;
		m_xArrow->SetVisibility(bEnable);
		m_yArrow->SetVisibility(bEnable);
		m_zArrow->SetVisibility(bEnable);

		if (bEnable)
		{
			m_xArrow->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			m_yArrow->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			m_zArrow->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		}
		else
		{
			m_xArrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
			m_yArrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
			m_zArrow->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		}
	}
}

