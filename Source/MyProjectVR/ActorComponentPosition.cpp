// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponentPosition.h"


// Sets default values for this component's properties
UActorComponentPosition::UActorComponentPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 0.f;
	// ...
}


// Called when the game starts
void UActorComponentPosition::BeginPlay()
{
	Super::BeginPlay();

	FVector MyCharacterLocation = GetOwner()->GetActorLocation();
	FRotator MyCharacterRotation = GetOwner()->GetActorRotation();
	FString NameIDMyCharacter = GetOwner()->GetActorLabel();

	//A doua optiune pentru a recupera la position 
	FString MyCharacterPosition = GetOwner()->GetTransform().GetLocation().ToString();
	
	UE_LOG(LogTemp, Warning, TEXT("%s Player Name is : %s %s"), *NameIDMyCharacter, *MyCharacterLocation.ToString(), *MyCharacterRotation.ToString(), *MyCharacterRotation.ToString());


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Blue, FString::Printf(TEXT("Player Name is : %s"), *MyCharacterLocation.ToString() ));
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Blue, FString::Printf(TEXT("Player Name is : %s"),  *NameIDMyCharacter));
		
	}
	

	// ...

}


// Called every frame
void UActorComponentPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FRotator MyCharacterNewRotation = FRotator(PitchValue, YawValue, RollValue);
	GetOwner()->SetActorRotation(MyCharacterNewRotation);

	
	// ...
}

