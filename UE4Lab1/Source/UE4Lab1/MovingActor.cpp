// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"


// Sets default values
AMovingActor::AMovingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentPoint = nullptr;
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	MoveToNextPoint();
	
}

// Called every frame
// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // If FirstPoint or SecondPoint is not set, exit early
    if (!FirstPoint || !SecondPoint)
    {
        return;
    }

    // If CurrentPoint is set, handle movement and rotation
    if (CurrentPoint)
    {
        // Calculate the displacement (delta) between this actor's location and the CurrentPoint's location
        FVector Delta = CurrentPoint->GetActorLocation() - GetActorLocation();
        
        // Determine the distance to the CurrentPoint
        float Distance = Delta.Size();

        // If the distance is less than 100 units, move to the next point
        if (Distance < 100.0f)
        {
            MoveToNextPoint();
        }

        // Determine the new look-at rotation based on the direction (forward axis, X)
        FRotator NewLookAt = FRotationMatrix::MakeFromX(Delta).Rotator();

        // Set pitch and roll to zero, only adjust yaw
        NewLookAt.Pitch = 0.0f;
        NewLookAt.Roll = 0.0f;

        // Smoothly interpolate the actor's current rotation to face the new direction
        FQuat TargetRotation = FQuat(NewLookAt);
        FQuat CurrentRotation = GetActorQuat();
        
        // Use SLERP (Spherical Linear Interpolation) for smooth rotation
        FQuat SlerpedRotation = FMath::QInterpTo(CurrentRotation, TargetRotation, DeltaTime, 2.0f);  // 2.0f is the interpolation speed
        SetActorRotation(SlerpedRotation);

        // Smoothly interpolate the actor's location towards the CurrentPoint's location
        FVector LerpLocation = FMath::VInterpConstantTo(GetActorLocation(), CurrentPoint->GetActorLocation(), DeltaTime, 600.0f);
        SetActorLocation(LerpLocation);
    }
}



void AMovingActor::MoveToNextPoint()
{
    // If the CurrentPoint is null or the CurrentPoint is SecondPoint, switch to FirstPoint
    if (CurrentPoint == nullptr || CurrentPoint == SecondPoint)
    {
        CurrentPoint = FirstPoint;
    }
    else
    {
        // Otherwise, switch to SecondPoint
        CurrentPoint = SecondPoint;
    }
}


