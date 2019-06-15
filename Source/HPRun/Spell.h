// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Spell.generated.h"

UCLASS()
class HPRUN_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* OurParticleSystem;
	UPROPERTY(EditAnywhere)
		USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SphereVisual;
	UPROPERTY(EditAnywhere)
		float rotSpeed;
	float rotSpeedX;
	float rotSpeedY;
};
