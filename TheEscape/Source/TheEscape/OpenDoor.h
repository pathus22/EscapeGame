// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



private:
	//UFUNCTION()
	void OnOverlap(AActor* OtherActor);
	UPROPERTY(EditInstanceOnly) ATriggerVolume* PressurePlate;
	TArray<AActor*> ActorsOverlapping;
	UPROPERTY(EditInstanceOnly) bool bIsOpen = false;
	UPROPERTY(EditInstanceOnly) float fOpenAngle = 110.0f;
	UPROPERTY(EditInstanceOnly) float fCloseDoorTimer = 3.0f;
	UPROPERTY(EditInstanceOnly) float TotalMass = 0.0f;
	float CloseTime = 0.0f;
	void OpenDoor();
	void CloseDoor();
	float GetOverlappingActorsMass();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
