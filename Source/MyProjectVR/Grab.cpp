// Fill out your copyright notice in the Description page of Project Settings.


#include "Grab.h"

#define OUT

// Sets default values for this component's properties
UGrab::UGrab()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
;	// ...
}


// Called when the game starts
void UGrab::BeginPlay()
{
	Super::BeginPlay();

	GetPhysicsHandle();
	SetUpInputComponent();
	// ...
	
}


// Called every frame
void UGrab::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	UE_LOG(LogTemp, Warning, TEXT("Viewpoint pos = %s & Viewpoint rot = %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	// Moi je pense que t'es un bébé !
	//FVector LineTraceEnd = PlayerViewPointLocation + FVector(0.0f, 0.0f, 100.0f);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachDistanceLine;
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255,0,0,1), false, 0.f, 0.f, 10.f);
	
	FCollisionQueryParams TraceParameters(FName(TEXT(" ")), false, GetOwner());


	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, 
		PlayerViewPointLocation, LineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	AActor* ActorTouchedByHit = hit.GetActor();

	if (ActorTouchedByHit)
	{
		UE_LOG(LogTemp, Warning, TEXT(" OUI"));
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{

		UE_LOG(LogTemp, Error, TEXT("Input ready to use! "));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrab::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrab::Released);
	}
	else
	{

		UE_LOG(LogTemp, Error, TEXT("%s missiong inputs component"), *GetOwner()->GetActorLabel());
	}

	// ...
}

void UGrab::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT(" missiong inputs component"));
}

void UGrab::Released()
{
	UE_LOG(LogTemp, Warning, TEXT(" missiong inputs component2222"));
}

void UGrab::GetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s dosent't have the physics handle component"), *GetOwner()->GetActorLabel());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s dosent't have the physics handle component"), *GetOwner()->GetActorLabel());
	}
}

void UGrab::SetUpInputComponent()
{
	/*InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{

		UE_LOG(LogTemp, Error, TEXT("Input ready to use! "));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrab::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrab::Released);
	}
	else
	{

		UE_LOG(LogTemp, Error, TEXT("%s missiong inputs component"), *GetOwner()->GetActorLabel());
	}*/
}


FVector UGrab::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

FVector UGrab::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachDistanceLine;
}



