// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "HousePlayer.generated.h"

class UMotionControllerComponent;
class AFurniture;

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* m_leftController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* m_rightController;
	
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

private:
	AFurniture* m_selectedFurniture;

	bool m_isLeftTriggerPressing;
	bool m_isRightTriggerPressing;
	bool m_isLeftGripPressing;
	bool m_isRightGripPressing;

	FVector m_leftControlLastPos;
	FVector m_rightControlLastPos;

	FRotator m_leftControlLastRot;
	FRotator m_rightControlLastRot;
};
