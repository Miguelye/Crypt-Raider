// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h" 


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetPhysicsHandle();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released grabber"));
}

void UGrabber::Grab()
{
	FVector Start = GetComponentLocation(); //Start Location of the Ray Line
	FVector End = Start + GetForwardVector() * MaxGrabDistance; //End Location of the Ray Line
	DrawDebugLine(GetWorld(), Start, End, FColor::Red); //Draws the rayline for debugging
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius); //creates a sphere which is going to traverse the distance by SweepSingleByChannel
	FHitResult HitResult; //Object that collided by the sphere

	//Traces a line and the sweeps it with the desire shape and adds the first object collided to the HitResult variable.
	//FQuat::Identity Returns 0
	//ECC_GameTraceChannel12 is the channel of Grabber.
	bool HadHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

	if (HadHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Actor"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	//Get a Component from the same actor
	UPhysicsHandleComponent* Result = GetOwner()->GetComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	return Result;
}