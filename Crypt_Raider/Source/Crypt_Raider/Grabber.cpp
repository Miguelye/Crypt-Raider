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
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}

	UE_LOG(LogTemp, Display, TEXT("Released grabber"));
}

void UGrabber::Grab()
{
	FHitResult HitResult; //Object we trying to grab

	if (GetGrabbableInReach(HitResult))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies(); //Ensures simulation is running for all bodies in this component

		PhysicsHandle->GrabComponentAtLocationWithRotation(	
			HitComponent,									//Component we want to grab
			NAME_None,										//name of the part of the component we want to grab
			HitResult.ImpactPoint,							//Location
			GetComponentRotation()							//Rotation
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

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult)
{
	FVector Start = GetComponentLocation(); //Start Location of the Ray Line
	FVector End = Start + GetForwardVector() * MaxGrabDistance; //End Location of the Ray Line
	DrawDebugLine(GetWorld(), Start, End, FColor::Red); //Draws the rayline for debugging
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5); //Draws a sphere at the end of the reach distance

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius); //creates a sphere which is going to traverse the distance by SweepSingleByChannel

	//Traces a line and then sweeps it with the desire shape and adds the first object collided to the HitResult variable.
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,								//Object that collided by the sphere
		Start,										//Start location of the sweep
		End,										//End location of the sweep
		FQuat::Identity,							//FQuat::Identity Returns 0
		ECC_GameTraceChannel2,						//ECC_GameTraceChannel12 is the channel of Grabber.
		Sphere);									//Shape of the object to perform the sweep with.
}