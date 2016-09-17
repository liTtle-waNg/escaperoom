// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Log, TEXT("Grab Key Pressed"))

	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInreach();

	/// Try and reach any actors with physics body collision channel set

	///If we hit something then attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Log, TEXT("Grab Key Released"))

	///Release physics handle
}

void UGrabber::FindPhysicsHandleComponent()
{
	/// Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The Physics handle is missing from %s"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	///Look for attached input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		//Input component is found
		UE_LOG(LogTemp, Log, TEXT("The Input Component has been found attached to %s!"), *GetOwner()->GetName())
			/// Bind the input axis
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		//input component has not been found
		UE_LOG(LogTemp, Error, TEXT("The Input Component is missing from %s"), *GetOwner()->GetName())
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInreach()
{
	///Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	//Draw a red trace in the world to visualize
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
	///Setup query params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	///Line trace (AKA Ray-cast out to reach distance)
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	///See what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()))
	}
	return FHitResult();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//if the physics handle is attached
		//move the object that we're holding

}

