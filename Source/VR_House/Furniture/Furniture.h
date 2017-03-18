// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MoveAxis/MoveAxis.h"
#include "Furniture.generated.h"

/**
 * 
 */
UCLASS()
class VR_HOUSE_API AFurniture : public AMoveAxis
{
	GENERATED_BODY()
	
public:
	AFurniture();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_furnitureMesh;

};
