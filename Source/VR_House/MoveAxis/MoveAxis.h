// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MoveAxis.generated.h"

UCLASS()
class VR_HOUSE_API AMoveAxis : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveAxis();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	void SetMoveAxisEnable(bool bEnable);


protected:
	UPROPERTY(BlueprintReadOnly)
	UArrowComponent* m_xArrow;

	UPROPERTY(BlueprintReadOnly)
	UArrowComponent* m_yArrow;

	UPROPERTY(BlueprintReadOnly)
	UArrowComponent* m_zArrow;
	
private:
	USceneComponent* m_rootComponent;
	
};
