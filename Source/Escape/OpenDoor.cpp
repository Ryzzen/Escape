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
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Trigger && Trigger->IsOverlappingActor(DoorOwner))
		OpenDoor();
	else
		CloseDoor();
}

void UOpenDoor::OpenDoor() const
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.f, OpenAngle, 0.f);

	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor() const
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.f, CloseAngle, 0.f);

	Owner->SetActorRotation(NewRotation);
}

