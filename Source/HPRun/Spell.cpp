// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"
#include "ConstructorHelpers.h"

// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rotSpeed = 1.0f;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	FVector location = SphereComponent->GetComponentLocation();
	SphereComponent->SetWorldLocation(FVector(200, 0, 0));

	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(1.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Spell"));

	
	//RootComponent->SetWorldLocation(FVector(590, -520, 350));
	//SphereComponent->SetWorldLocation(FVector(590, -520, 350));
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	//SphereVisual->SetWorldLocation(FVector(590, -520, 350));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Pipe"));
	if (SphereVisualAsset.Succeeded())
	{
		//float angleAxis = FMath::RandRange(0.0f, 360.0f);
		// FRotator NewRotation = FRotator(0, angleAxis, 0);
		// float z = FMath::RandRange(-250.0f, 250.0f);
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetWorldLocation(location);
		SphereVisual->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		SphereVisual->SetRelativeScale3D(FVector(0.5f));

		//SphereVisual->SetRelativeLocation(FVector(-200.0f, 0.0f, 0.0f));
		//SetActorRotation(NewRotation);
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = true;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	OurParticleSystem->SetRelativeScale3D(FVector(0.001f));
	OurParticleSystem->SetRelativeRotation(FRotator(90.0f, 90.0f, 90.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Smoke.P_Smoke"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
	//FVector Locations = SphereVisual->SetWorldLocation();
		rotSpeedX = 0;
		rotSpeedY = 0;

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	rotSpeedX = 200 * sin(rotSpeed);
	rotSpeedY = -200 * cos(rotSpeed);
	rotSpeed += 0.01;
	SphereComponent->AddRelativeLocation(FVector(rotSpeedX, rotSpeedY, 0));
	//SphereComponent->AddRelativeRotation(FRotator(0.0f, DeltaTime * rotSpeed, 0.0f));

}

