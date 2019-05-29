// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"

#include "Potter.generated.h"

UCLASS()
class HPRUN_API APotter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APotter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float angleAxis;
	float verticalMove;
	float speed = 1;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;
	UPROPERTY(EditAnywhere, Category = Movement)
	FVector dimensions;
	UPROPERTY(EditAnywhere, Category = Movement)
	FVector axisVector;
	UPROPERTY(EditAnywhere, Category = Movement)
	float multiplier;

	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	// Input variables
	FVector CurrentVelocity;
	bool bMovingUp;
	bool bMovingDown;

	float angle_axis;
};
