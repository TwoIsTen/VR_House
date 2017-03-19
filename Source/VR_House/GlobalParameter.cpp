// Fill out your copyright notice in the Description page of Project Settings.

#include "VR_House.h"
#include "GlobalParameter.h"

AGlobalParameter* GlobalParameterReader::m_parameter = nullptr;

// Sets default values
AGlobalParameter::AGlobalParameter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGlobalParameter::BeginPlay()
{
	GlobalParameterReader::SetParameter(this);
}

AGlobalParameter* GlobalParameterReader::GetParameter()
{
	return m_parameter;
}

void GlobalParameterReader::SetParameter(AGlobalParameter* parameter)
{
	m_parameter = parameter;
}
