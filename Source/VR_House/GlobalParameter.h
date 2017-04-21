// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Furniture/Furniture.h"
#include "UserWidget.h"
#include "GlobalParameter.generated.h"

UENUM(BlueprintType)
namespace EFurnitureType
{
	enum Type
	{
		Table = 0,
		Seat,
		Bed,
		Chest,
		Decoration,
		Other
	};
}

UENUM(BlueprintType)
namespace EMenuType
{
	enum Type
	{
		Menu = 0,
		Place,
		Delete,

		Quit
	};
}

/*
// parameters.
*/
USTRUCT(Blueprintable)
struct FHouseParamter : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UDataTable* FurnitureTypeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UDataTable* Furniturecategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	TSubclassOf<UUserWidget> MenuBackgroundWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	TSubclassOf<UUserWidget> SelectFrameWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UDataTable* MainMenuData;
};


USTRUCT(Blueprintable)
struct FFurnitureTypeName : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	TEnumAsByte<EFurnitureType::Type> Type = EFurnitureType::Table;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	FName Typename = "Typename";
};

USTRUCT(Blueprintable)
struct FFurnitureCategory : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	TEnumAsByte<EFurnitureType::Type> Type = EFurnitureType::Table;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
		UDataTable* FurnitureTable;
};

USTRUCT(Blueprintable)
struct FFurnitureTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	int32 Index = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	TSubclassOf<AFurniture> Furniture;
};

USTRUCT(Blueprintable)
struct FMenuInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	TSubclassOf<UUserWidget> Widget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	TEnumAsByte<EMenuType::Type> Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	FVector2D DrawSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	UDataTable* MenuContent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	TSubclassOf<AFurniture> FurnitureClass;
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