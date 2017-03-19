// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GlobalParameter.generated.h"

UCLASS()
class VR_HOUSE_API AGlobalParameter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobalParameter();

	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
	UDataTable* HandModel;

};


class GlobalParameterReader
{
public:

public:
	static AGlobalParameter* GetParameter();
	static void SetParameter(AGlobalParameter* parameter);
private:
	static AGlobalParameter* m_parameter;
};

USTRUCT()
struct FHandModel : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UStaticMesh* Model;
};