// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/TriggerVolume.h>
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECTVR_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor();
	void CloseDoor();
	void RotateDoor(bool bOpen);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 90.0f;

	UPROPERTY(VisibleAnywhere)
		float CoolDownOpenDoor;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.0f;
	
		float LastDoorOpenTime;

		float TimeDoorOpen;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *  PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	
	AActor* Owner;

};
