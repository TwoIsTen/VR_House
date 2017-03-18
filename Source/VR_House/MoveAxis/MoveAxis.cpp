// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "MoveAxis.h"


// Sets default values
AMoveAxis::AMoveAxis()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(m_rootComponent);

	m_xArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("X Axis"));
	m_xArrow->AttachToComponent(m_rootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_xArrow->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	m_xArrow->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	m_xArrow->SetArrowColor_New(FLinearColor::Red);
	m_xArrow->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	m_xArrow->SetRenderCustomDepth(true);
	m_xArrow->SetCustomDepthStencilValue(0);
	m_xArrow->SetHiddenInGame(false);

	m_yArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Y Axis"));
	m_yArrow->AttachToComponent(m_rootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_yArrow->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	m_yArrow->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	m_yArrow->SetArrowColor_New(FLinearColor::Yellow);
	m_yArrow->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	m_yArrow->SetRenderCustomDepth(true);
	m_yArrow->SetCustomDepthStencilValue(255);
	m_yArrow->SetHiddenInGame(false);

	m_zArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Z Axis"));
	m_zArrow->AttachToComponent(m_rootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	m_zArrow->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	m_zArrow->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	m_zArrow->SetArrowColor_New(FLinearColor::Blue);
	m_zArrow->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	m_zArrow->SetRenderCustomDepth(true);
	m_zArrow->SetCustomDepthStencilValue(255);
	m_zArrow->SetHiddenInGame(false);

	//SetMoveAxisEnable(false);
}

// Called when the game starts or when spawned
void AMoveAxis::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveAxis::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMoveAxis::SetMoveAxisEnable(bool bEnable)
{
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

