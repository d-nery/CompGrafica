// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Enemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Components/TextRenderComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"
UCLASS()
class HPRUN_API ASpawner : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ASpawner();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		FVector Location;
	UPROPERTY(EditAnywhere)
		FRotator Rotation;
	int32 CountdownTime;

	UTextRenderComponent* CountdownText;

	void UpdateTimerDisplay();

	void AdvanceTimer();

	void CountdownHasFinished();

	FTimerHandle CountdownTimerHandle;

	int a = 0;
};
