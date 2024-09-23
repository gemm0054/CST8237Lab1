// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitActor.h"


// Sets default values
AOrbitActor::AOrbitActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentAngle = InitialRotationAngle;
}

// Called when the game starts or when spawned
void AOrbitActor::BeginPlay()
{
	Super::BeginPlay();

	Reset();
	
}

// Called every frame
void AOrbitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RotateAroundActor != nullptr)
	{
		// Increment CurrentAngle by RotationSpeed * DeltaTime
		CurrentAngle += RotationSpeed * DeltaTime;

		// Wrap around if CurrentAngle exceeds 360 degrees
		if (CurrentAngle > 360.0f)
		{
			CurrentAngle -= 360.0f;
		}

		// Define the rotation axis for vertical rotation (pitch)
		const FVector RotationAxis = FVector::RightVector;  // This rotates around the right axis (X-axis)

		// Calculate the new location using RotateAngleAxis for vertical rotation
		const FVector NewLocation = RotateAroundActor->GetActorLocation() + 
									RotationRadius.RotateAngleAxis(CurrentAngle, RotationAxis);

		// Create a quaternion rotation (set pitch, yaw, roll)
		FQuat NewRotation = FRotator(CurrentAngle, 0.0f, 0.0f).Quaternion(); // Set pitch to CurrentAngle, yaw and roll to 0

		// Set the actor's location and rotation
		SetActorLocationAndRotation(NewLocation, NewRotation);
	}

	
}

void AOrbitActor::Reset()
{
	CurrentAngle = InitialRotationAngle;

	if (!RotateAroundActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("RotateAroundActor is not set."));
		return;
	}

	if (RotationRadius.IsZero())
	{
		RotationRadius = GetActorLocation() - RotateAroundActor->GetActorLocation();
	}
}


