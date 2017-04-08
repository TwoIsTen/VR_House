// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MoveAxis.generated.h"

class AHousePlayer;

UCLASS()
class VR_HOUSE_API AMoveAxis : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveAxis();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	void SetMoveAxisEnable(bool bEnable);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_xArrow;

protected:
	UPROPERTY(BlueprintReadOnly)
	UArrowComponent* m_yArrow;

	UPROPERTY(BlueprintReadOnly)
	UArrowComponent* m_zArrow;
	
protected:
	USceneComponent* m_axisRootComponent;

private:
	bool m_active;
	static AHousePlayer* m_mainPlayer;
	USceneComponent* m_rootComponent;

	
};
