// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "Enemy.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	//CountdownText->SetHorizontalAlignment(EHTA_Center);
	//CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;

	CountdownTime = 3;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//FVector Location(0.0f, 0.0f, 0.0f);
	//FRotator Rotation(0.0f, 0.0f, 0.0f);
	//FActorSpawnParameters SpawnInfo;
	//GetWorld()->SpawnActor<ABlock>(Location, Rotation, SpawnInfo);
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ASpawner::AdvanceTimer, 1.0f, true);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::UpdateTimerDisplay()
{

}

void ASpawner::AdvanceTimer()
{
	// We're done counting down, so stop running the timer.
	//GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	//Perform any special actions we want to do when the timer ends.
	//float x = FMath::RandRange(-10.0f, 10.0f)
	//float y = FMath::RandRange(float -10.0f, float  10.0f)
	float z = FMath::RandRange(-5000.0f, 5000.0f);
	Location = FVector(0, 0, 0);
	Rotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	GetWorld()->SpawnActor<AEnemy>(Location, Rotation, SpawnInfo);

}