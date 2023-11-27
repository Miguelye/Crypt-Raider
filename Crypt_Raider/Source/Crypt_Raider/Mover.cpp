// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		//current
		FVector CurrentLocation = GetOwner()->GetActorLocation(); //Get the current locatio of the actor EACH TICK
		//target
		FVector TargetLocation = originalLocation + MoveOffSet; //Destination which the actor should reach
		//speed
		float Speed = FVector::Distance(originalLocation, TargetLocation) / MoveTime; //Velocity equation V=D/T, D is the distance from original location to the final location, T is the time it takes to get there
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed); //Calculates the new location for the next Tick until it reaches the final destination
		GetOwner()->SetActorLocation(NewLocation); //Set the actor's location for the next tick
	}
	// ...
}

