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


	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius); //creates a sphere which is going to traverse the distance by SweepSingleByChannel
	FHitResult HitResult; //Object that collided by the sphere

	//Traces a line and the sweeps it with the desire shape and adds the first object collided to the HitResult variable.
	//FQuat::Identity Return 0
	//ECC_GameTraceChannel12 is the channel of Grabber.
	bool HadHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);

	if (HadHit)
	{
		FString Name = HitResult.GetActor()->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Objects Hit: %s"), *Name);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Actor"));
	}
}