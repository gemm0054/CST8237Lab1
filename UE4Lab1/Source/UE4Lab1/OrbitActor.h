// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "OrbitActor.generated.h"

UCLASS()
class UE4LAB1_API AOrbitActor : public ABaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOrbitActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
	AActor* RotateAroundActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
	float RotationSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
	FVector RotationRadius = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround", meta = (ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0", UIMax = "360.0"))
	float InitialRotationAngle = 0.f;

	void Reset();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CurrentAngle = 0.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
