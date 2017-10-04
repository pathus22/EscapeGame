// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

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
	Player = GetWorld()->GetFirstPlayerController();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Player->GetPlayerViewPoint(OUT viewPoint,OUT viewRotation);
	//UE_LOG(LogTemp, Warning, TEXT("View Point : %s -- View Rotation : %s"), *viewPoint.ToString(), *viewRotation.ToString());
	EndOfView = viewPoint + (viewRotation.Vector()*fMaxReach);
	GetWorld()->LineTraceSingleByObjectType(OUT hit, viewPoint, EndOfView, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), ColQueryParams);
	ActorHitted = hit.GetActor();
	if (ActorHitted)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hiiting the %s"), *ActorHitted->GetName());
	}
	DrawDebugLine(GetWorld(), viewPoint+FVector(0.0f,.1f,0.0f), EndOfView, FColor::Green, false, 0.0f, (uint8)'\000', 1.0f);
	// ...
}

