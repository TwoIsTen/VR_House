// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GlobalParameter.generated.h"

/*
// parameters.
*/
USTRUCT(Blueprintable)
struct FHouseParamter : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	FName LogoGPLevelName = "LogoA";
};

UCLASS()
class VR_HOUSE_API AGlobalParameterReader : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE static const FHouseParamter* GetParameter()
	{
#if WITH_EDITOR
		if (s_param)
		{
			return s_param;
		}
		else
		{
			AGlobalParameterReader* reader = FindObjectSafe<AGlobalParameterReader>(
				ANY_PACKAGE, TEXT("GlobalParameter"), true);
			if (reader)
			{
				return reader->m_globalData->FindRow<FHouseParamter>(TEXT("Param"),
					"Get config by editor");
			}
			else
			{
				check(false);
				return nullptr;
			}
		}
#else
		check(s_param);
		return s_param;
#endif
	}

public:
	// Sets default values for this actor's properties
	AGlobalParameterReader();

	virtual void PostInitializeComponents() override;

	// Called when the game ends or when de-spawned
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	UDataTable* m_globalData;

private:
	static const FHouseParamter* s_param;
};