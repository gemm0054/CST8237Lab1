// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "MovingActor.generated.h"

UCLASS()
class UE4LAB1_API AMovingActor : public ABaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingActor();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement Point")
	AActor* FirstPoint;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement Point")
	AActor* SecondPoint;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//void MoveToNextPoint();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* CurrentPoint;
	
	void MoveToNextPoint();
};
