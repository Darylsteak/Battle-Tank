// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Math/Vector.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to Super as we'e replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct
	(
		TankForward,
		AIForwardIntention
	);

	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct
	(
		TankForward,
		AIForwardIntention
	);

	IntendTurnRight(RightThrow.Z);

	//UE_LOG(LogTemp,Warning,TEXT("MoveVelocity of %s = %s"), *TankName, *MoveVelocityString)
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	

	//TODO prevent extra speed (double) due to use of both controls (track only and fly by wire)
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//TODO prevent extra speed (double) due to use of both controls (track only and fly by wire)
}
