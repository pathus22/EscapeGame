// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

void UOpenDoor::OnOverlap(AActor * OtherActor)
{
	OpenDoor();
}

void UOpenDoor::OpenDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.0f, fOpenAngle, 0.0f));
	bIsOpen = true;
}

void UOpenDoor::CloseDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	bIsOpen = false;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("TIME: %f"), CloseTime);
	CloseTime += GetWorld()->GetDeltaSeconds();
	TotalMass = GetOverlappingActorsMass();
	if (TotalMass > 81.0f)
	{
		CloseTime = 0.0f;
		OpenDoor();
	}
	if (CloseTime > fCloseDoorTimer)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetOverlappingActorsMass()
{
	float fActualTotalMass = 0.0f;
	PressurePlate->GetOverlappingActors(ActorsOverlapping);
	
	for (INT32 i = 0; i < ActorsOverlapping.Num(); i++)
	{
		if (ActorsOverlapping[i] != nullptr)
		{
			fActualTotalMass += ActorsOverlapping[i]->GetRootPrimitiveComponent()->GetMass();
		}
	}
	return fActualTotalMass;
}
