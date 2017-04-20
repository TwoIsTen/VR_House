// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "Furniture.h"




AFurniture::AFurniture()
{
	PrimaryActorTick.bCanEverTick = true;

	//m_root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//m_root->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//m_root->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

void AFurniture::BeginPlay()
{
	Super::BeginPlay();
	TArray<UActorComponent*> mesh = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (int i = 0, n = mesh.Num(); i < n; ++i)
	{
		UStaticMeshComponent* temp = Cast<UStaticMeshComponent>(mesh[i]);
		temp->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
		temp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		temp->SetNotifyRigidBodyCollision(true);
		temp->OnComponentBeginOverlap.AddDynamic(this, &AFurniture::OnBeginOverLap);
	}
}

void AFurniture::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFurniture::PrepareToMove()
{
	TArray<UActorComponent*> mesh = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (int i = 0, n = mesh.Num(); i < n; ++i)
	{
		UStaticMeshComponent* temp = Cast<UStaticMeshComponent>(mesh[i]);
		temp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		temp->SetEnableGravity(false);
		temp->SetMobility(EComponentMobility::Movable);
	}
}

void AFurniture::MoveFinished()
{
	TArray<UActorComponent*> mesh = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (int i = 0, n = mesh.Num(); i < n; ++i)
	{
		UStaticMeshComponent* temp = Cast<UStaticMeshComponent>(mesh[i]);
		temp->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
		temp->SetEnableGravity(true);
		temp->SetMobility(EComponentMobility::Static);
	}
}

void AFurniture::OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	PRINT_ON_SCREEN(FColor::Blue ,"Hit something by mesh %s", *OtherActor->GetName());
}
