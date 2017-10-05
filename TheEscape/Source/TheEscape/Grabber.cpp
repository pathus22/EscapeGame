// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

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
	FindPlayerController();
	FindPhysicHandler();
	MapInputs();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (pyHandle->GrabbedComponent)
	{
		CalculateEndOfView();
		pyHandle->SetTargetLocation(EndOfView);
	}
}

///Actions of Grab
void UGrabber::Grab()
{
	CalculateRayCast();
	UPrimitiveComponent* ComponentToGrab = hit.GetComponent();
	//UE_LOG(LogTemp, Warning, TEXT("Im Grabbing!"));
	if (ActorHitted != nullptr)
	{
		pyHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}
///End of Action of Grab
void UGrabber::Release()
{
	ActorHitted = nullptr;
	pyHandle->ReleaseComponent();
	//UE_LOG(LogTemp, Warning, TEXT("Im Releasing!"));
}


#pragma region Private Methods

void UGrabber::CalculateRayCast()
{
	CalculateEndOfView();
	GetWorld()->LineTraceSingleByObjectType(OUT hit, viewPoint, EndOfView, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), ColQueryParams);
	ActorHitted = hit.GetActor();

	///OPTIONAL - Log view point vector And View rotation vector
	//UE_LOG(LogTemp, Warning, TEXT("View Point : %s -- View Rotation : %s"), *viewPoint.ToString(), *viewRotation.ToString());

	///OPTIONAL - Draw a Line From the player To the max Range of the grabber
	//DrawDebugLine(GetWorld(), viewPoint + FVector(0.0f, .1f, 0.0f), EndOfView, FColor::Green, false, 0.0f, (uint8)'\000', 1.0f);
}

void UGrabber::MapInputs()
{
	playerInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	playerInputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
	playerInputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
}

void UGrabber::FindPhysicHandler()
{
	pyHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

void UGrabber::FindPlayerController()
{
	Player = GetWorld()->GetFirstPlayerController();
}

void UGrabber::CalculateEndOfView()
{
	Player->GetPlayerViewPoint(OUT viewPoint, OUT viewRotation);
	EndOfView = viewPoint + (viewRotation.Vector()*fMaxReach);
}
#pragma endregion


