// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GlobalParameter.h"
#include "HousePlayer.generated.h"

class UMotionControllerComponent;
class UWidgetComponent;
class AFurniture;

UENUM(BlueprintType)
namespace EPlayerState
{
	enum Type
	{
		Free = 0,
		Laser,
		SelectFurniture,
		MoveFurniture,
		RotateFurniture,
		OnMainMenu,
	};
}

UENUM(BlueprintType)
namespace EMenuType
{
	enum Type
	{
		MainMenu = 0,
	};
}

UCLASS()
class VR_HOUSE_API AHousePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AHousePlayer();

public:
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:
	void MoveForward(float distance);
	void MoveRight(float distance);
	void LookUp(float angle);
	void LookRight(float angle);
	void Debug_SetControllByKeyBoard();
	FVector GetCameraLocation();

public:
	//input function
	void StartUseLeftTrigger();
	void EndUseLeftTrigger();
	void StartUseRightTrigger();
	void EndUseRightTrigger();
	void StartUseLeftGrip();
	void EndUseLeftGrip();
	void StartUseRightGrip();
	void EndUseRightGrip();
	void StartUseLeftMenu();
	void StartUseRightMenu();
	void ShowMenu(EMenuType::Type type, bool isLeft);

private:
	void UpdateMenuBackGround(float DeltaTime);
	void UpdateSelectFrame(float DeltaTime);
	void StopLaser(bool isLeft);
	void TickState_SelectFurniture();
	void TickState_RotateFurniture();
	void TickState_MoveFurniture();
	void MakeMenu();
	UWidgetComponent* GenerateWidgetComponent(FName& name);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_scaleTime = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* m_leftController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* m_rightController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_cameraRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* m_cameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_leftHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_rightHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_leftTraceStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_rightTraceStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_leftTraceEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_rightTraceEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_leftLaser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* m_rightLaser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_menuAttachNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* m_menuBackGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* m_selectFrame;

private:
	AFurniture* m_selectedFurniture;

	bool m_isLeftTriggerPressing;
	bool m_isRightTriggerPressing;
	bool m_isLeftGripPressing;
	bool m_isRightGripPressing;

	float m_times;
	float m_menuScaleX;
	float m_menuScaleY;
	float m_scaleProgress;
	float m_menuScaleSpeedX;
	float m_menuScaleSpeedY;
	float m_selectScaleX;
	float m_selectScaleY;
	float m_selectScaleSpeedX;
	float m_selectScaleSpeedY;
	float m_selectScaleProgress;

	FVector m_leftControlLastPos;
	FVector m_rightControlLastPos;

	FVector m_leftControlCurrentPos;
	FVector m_rightControlCurrentPos;
	FVector m_leftControlDeltaPos;
	FVector m_rightControlDeltaPos;

	FRotator m_leftControlLastRot;
	FRotator m_rightControlLastRot;

	FRotator m_leftControlCurrentRot;
	FRotator m_rightControlCurrentRot;
	FRotator m_leftControlDeltaRot;
	FRotator RightControlDeltaRot;

	EPlayerState::Type m_playerState;

	TArray<FMenuInfo*> m_menuContents;
};
