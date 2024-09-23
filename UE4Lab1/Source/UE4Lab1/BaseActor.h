// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS(abstract)
class UE4LAB1_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

	UPROPERTY(EditAnywhere, Category = "Actor Components")
	class USceneComponent* ActorRootComponent;

	UPROPERTY(EditAnywhere, Category = "Actor Components")
	class UStaticMeshComponent* ActorMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
