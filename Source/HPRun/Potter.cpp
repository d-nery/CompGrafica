// Fill out your copyright notice in the Description page of Project Settings.


#include "Potter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APotter::APotter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-400.0f, 0.0f, 0.0f));
	OurCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	dimensions = FVector(10, 0, 0);
	axisVector = FVector(0, 0, 1);
	multiplier = 50.f;
}

// Called when the game starts or when spawned
void APotter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = OurVisibleComponent->GetRelativeTransform().GetTranslation();
	float currentRotation = OurVisibleComponent->GetRelativeTransform().GetRotation().Rotator().Roll;
	float step = 1.0f;

	if (bMovingUp) {
		currentRotation = FMath::Clamp(currentRotation + step, -20.0f, 20.0f);
	}
	else if (bMovingDown) {
		currentRotation = FMath::Clamp(currentRotation - step, -20.0f, 20.0f);
	}
	else {
		if (currentRotation > 0) {
			currentRotation = FMath::Clamp(currentRotation - step*2, 0.0f, 20.0f);
		}
		else if (currentRotation < 0) {
			currentRotation = FMath::Clamp(currentRotation + step*2, -20.0f, 0.0f);
		}
	}

	angleAxis += DeltaTime * multiplier * CurrentVelocity.Y * speed;
	verticalMove += DeltaTime * multiplier * CurrentVelocity.X;

	if (angleAxis > 360.0f) {
		angleAxis = 0;
	}

	FVector RotateValue = dimensions.RotateAngleAxis(angleAxis, axisVector);

	float newSpeed = NewLocation.Z + DeltaTime * multiplier * CurrentVelocity.X * speed;
	NewLocation.Z = FMath::Clamp(newSpeed, -100.0f, 100.0f);

	FRotator NewRotation = FRotator(0, angleAxis, 0);

	SetActorRotation(NewRotation);
	OurVisibleComponent->SetRelativeLocation(NewLocation);
	OurVisibleComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, currentRotation));
}

// Called to bind functionality to input
void APotter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Grow", IE_Pressed, this, &APotter::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &APotter::StopGrowing);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &APotter::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &APotter::Move_YAxis);
}

void APotter::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f);

	if (CurrentVelocity.X > 0) {
		bMovingUp = true;
		bMovingDown = false;
	}
	else if (CurrentVelocity.X < 0) {
		bMovingUp = false;
		bMovingDown = true;
	}
	else {
		bMovingDown = false;
		bMovingUp = false;
	}
}

void APotter::Move_YAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

void APotter::StartGrowing()
{
	speed = FMath::Clamp(speed + 1, 1.0f, 15.0f);
}

void APotter::StopGrowing()
{
	speed = FMath::Clamp(speed - 1, 1.0f, 15.0f);
}