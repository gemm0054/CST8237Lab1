﻿// Fill out your copyright notice in the Description page of Project Settings.

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
	float RotationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
