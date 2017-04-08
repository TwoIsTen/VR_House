// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "HousePlayer.generated.h"

class UMotionControllerComponent;

UCLASS()
class VR_HOUSE_API AHousePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHousePlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float distance);
	void MoveRight(float distance);
	void LookUp(float angle);
	void LookRight(float angle);
	void Debug_SetControllByKeyBoard();
	FVector GetCameraLocation();

	//input function
	void UseLeftTrigger();

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
};
