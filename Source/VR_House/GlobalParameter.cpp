// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "GlobalParameter.h"


//--------------------------------------------------------------------------------
// Sets default values
AGlobalParameterReader::AGlobalParameterReader()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AGlobalParameterReader::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(m_globalData);

	s_param = m_globalData->FindRow<FHouseParamter>("Param",
		"cache config for environment");
}


//--------------------------------------------------------------------------------
void AGlobalParameterReader::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	s_param = nullptr;
}

//--------------------------------------------------------------------------------
const FHouseParamter* AGlobalParameterReader::s_param = nullptr;

//--------------------------------------------------------------------------------
