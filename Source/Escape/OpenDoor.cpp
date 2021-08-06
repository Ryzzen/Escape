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

	Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnTrigger() >= MassOpenThreashold)
		OnOpen.Broadcast();
	else
		OnClose.Broadcast();
}

float UOpenDoor::GetTotalMassOnTrigger() const
{
	if (!Trigger)
		return 0.0f;

	float TotalMass = 0.f;

	TArray<AActor *> Actors;
	Trigger->GetOverlappingActors(Actors);

	for (const auto &Actor : Actors)
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

	return TotalMass;
}
