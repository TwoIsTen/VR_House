// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MoveAxis/MoveAxis.h"
#include "Furniture.generated.h"

/**
 * 
 */
UCLASS()
class VR_HOUSE_API AFurniture : public AActor
{
	GENERATED_BODY()
	
public:
	AFurniture();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void PrepareToMove();
	void MoveFinished();

public:
	UFUNCTION()
	void OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//USceneComponent* m_root;

};
