// Copyright Antoine Mayaud 2021.


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	DoorOwner = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Trigger && Trigger->IsOverlappingActor(DoorOwner)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		CloseDoor();
}

void UOpenDoor::OpenDoor() const
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor() const
{
	Owner->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}

