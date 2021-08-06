// Copyright Antoine Mayaud 2021.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor() const;
	void CloseDoor() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float GetTotalMassOnTrigger() const;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	float CloseAngle = 0.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* Trigger = nullptr;

	AActor* DoorOwner = nullptr;
	AActor* Owner = nullptr;

	float LastDoorOpenTime = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.f;

	UPROPERTY(EditAnywhere)
	float MassOpenThreashold = 150.f;
};
