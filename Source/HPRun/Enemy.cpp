// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "ConstructorHelpers.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rotSpeed = 10.0f;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(1.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Enemy"));
	RootComponent->SetWorldLocation(FVector(590, -520, 350));
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/Enemies/Dementor"));
	if (SphereVisualAsset.Succeeded())
	{
		float angleAxis = FMath::RandRange(0.0f, 360.0f);
		FRotator NewRotation = FRotator(0, angleAxis, 0);
		float z = FMath::RandRange(-250.0f, 250.0f);
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		// SphereVisual->SetRelativeLocation(FVector(350.0f, 0.0f, 0.0f));
		SphereVisual->SetRelativeRotation(FRotator(0.0f, 0.0f, 60.0f));
		SphereVisual->SetRelativeScale3D(FVector(0.8f));

		SphereVisual->SetRelativeLocation(FVector(-200.0f,0.0f, z));
		SetActorRotation(NewRotation);
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = true;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	OurParticleSystem->SetRelativeScale3D(FVector(0.5f));
	OurParticleSystem->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Smoke.P_Smoke"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereComponent->AddRelativeRotation(FRotator(0.0f, DeltaTime*rotSpeed, 0.0f));
}
