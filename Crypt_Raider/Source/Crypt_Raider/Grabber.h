// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPT_RAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

	UPhysicsHandleComponent* GetPhysicsHandle() const; //checks if we have a PhysicsHandle component if we do it returns it.
	bool GetGrabbableInReach(FHitResult& OutHitResult); //Checks if object that is grabbable is within reach
	
private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400; //Distance of the RayLine in cm

	UPROPERTY(EditAnywhere)
	float GrabRadius = 50;
	
	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	UPhysicsHandleComponent* PhysicsHandle;
};
