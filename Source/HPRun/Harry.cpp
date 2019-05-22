// Fill out your copyright notice in the Description page of Project Settings.


#include "Harry.h"

// Sets default values
AHarry::AHarry()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHarry::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHarry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHarry::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

