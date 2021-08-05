// Copyright Antoine Mayaud 2021.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MoveGrabedObject();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::GetReachVector(FVector& PlayerLocation, FVector& LineTraceEnd) const
{
	FRotator PlayerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerLocation,
		PlayerRotation
	);

	LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;
}

FHitResult UGrabber::RayCastInReach() const
{
	FVector PlayerLocation;
	FVector LineTraceEnd;

	GetReachVector(PlayerLocation, LineTraceEnd);

	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	return Hit;
}

void UGrabber::MoveGrabedObject()
{
	if (!PhysicsHandle || !PhysicsHandle->GrabbedComponent)
		return;

	FVector PlayerLocation;
	FVector LineTraceEnd;

	GetReachVector(PlayerLocation, LineTraceEnd);

	PhysicsHandle->SetTargetLocation(LineTraceEnd);
}

void UGrabber::Grab()
{
	FHitResult Hit = RayCastInReach();
	UPrimitiveComponent* GrabedComponent = Hit.GetComponent();

	if (GrabedComponent) {
		PhysicsHandle->GrabComponent(
			GrabedComponent,
			NAME_None,
			GrabedComponent->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle || !PhysicsHandle->GrabbedComponent)
		return;

	PhysicsHandle->ReleaseComponent();
}
