// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

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

	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ActorThatOpens == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(" Actor fide "));
	}

	if (TimeDoorOpen == 0)
	{
		TimeDoorOpen = 1;
	}
	CoolDownOpenDoor = TimeDoorOpen;


	//if (Owner == nullptr)UE_LOG(LogTemp, Error, TEXT(" Actor fide "));
		
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		RotateDoor(false);
		//CloseDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	
	}
	else
	{
		CoolDownOpenDoor -= DeltaTime;
		if (CoolDownOpenDoor <= 0)
		{
			RotateDoor(true);
			CoolDownOpenDoor = TimeDoorOpen;
			CoolDownOpenDoor++;
		}
		
		//OpenDoor();
	}
	// ...
}

void UOpenDoor::OpenDoor()
{
	
	UE_LOG(LogTemp, Warning, TEXT(" OpenThatDoor"));
	FRotator NewRotation = FRotator(0.f,  OpenAngle, 0.f);
	Owner->SetActorRotation(NewRotation);


	
}

void UOpenDoor::CloseDoor()
{

	UE_LOG(LogTemp, Warning, TEXT(" DoorClose"));
	FRotator NewRotation = FRotator(0.f, 0.f, 0.f);

	Owner->SetActorRotation(NewRotation);



}

void UOpenDoor::RotateDoor(bool bOpen)
{
	FRotator NewRotation = bOpen ? FRotator(0.f, OpenAngle, 0.f) : FRotator(0.f, 0.f, 0.f);
	Owner->SetActorRotation(NewRotation);
	UE_LOG(LogTemp, Warning, TEXT(" OpenThatDoor"));
	return;
}

