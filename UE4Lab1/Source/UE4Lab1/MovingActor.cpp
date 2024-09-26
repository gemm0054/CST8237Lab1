#include "MovingActor.h"

// Sets default values
AMovingActor::AMovingActor()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentPoint = nullptr;
	CurrentIndex = 0;  // Initialize the index to the first point
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	// Start by moving to the first point
	MoveToNextPoint();
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ensure there are enough points to move between
	if (Points.Num() == 0)
	{
		return;
	}

	// If the current point is valid, proceed with movement and rotation
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
		NewLookAt.Yaw += -180.0f;

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
	// Check if there are any points to move to
	if (Points.Num() == 0)
	{
		return;
	}

	// Move to the next point in the array
	CurrentIndex = (CurrentIndex + 1) % Points.Num();  // Cycle through points, wrapping back to the start
	CurrentPoint = Points[CurrentIndex];  // Set the next point
}
