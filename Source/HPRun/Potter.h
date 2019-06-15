// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Engine.h"
#include "Enemy.h"
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

	void Shooting();

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
	
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;

	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	


	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	// Input variables
	FVector CurrentVelocity;
	bool bMovingUp;
	bool bMovingDown;
	bool facingLeft;

	float angle_axis;
};
