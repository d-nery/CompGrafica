// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"
#include "ConstructorHelpers.h"

// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->rotSpeed = 100.0f;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	FVector location = SphereComponent->GetComponentLocation();

	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(1.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Spell"));

	
	RootComponent->SetWorldLocation(FVector(590, -520, 350));
	SphereComponent->SetWorldLocation(FVector(590, -520, 350));
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Pipe"));

	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetWorldLocation(location);
		SphereVisual->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		SphereVisual->SetRelativeScale3D(FVector(0.0005f));
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = true;
	OurParticleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	OurParticleSystem->SetRelativeScale3D(FVector(300.0f));
	OurParticleSystem->SetRelativeRotation(FRotator(90.0f, 90.0f, 90.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/TS_Fireworks/Particles/PS_TS_FireworksShell"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ASpell::AdvanceTimer, 2.0f, true);
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereComponent->AddRelativeRotation(FRotator(0.0f, DeltaTime * this->rotSpeed, 0.0f));
}

void ASpell::setLocation(FVector Location)
{
	SphereVisual->SetWorldLocation(Location);
	RootComponent->SetWorldLocation(FVector(590, -520, 350) + FVector(0, 0, 10));
}

void ASpell::goToLeft(bool facingLeft)
{
	if (!facingLeft)
	{
		this->rotSpeed *= -1;
	}
}

void ASpell::AdvanceTimer()
{
	Destroy();
}