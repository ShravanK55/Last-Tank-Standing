// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		UE_LOG(LogTemp, Warning, TEXT("One/more tracks not attached to the movement component!"))
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
	{
		UE_LOG(LogTemp, Warning, TEXT("One/more tracks not attached to the movement component!"))
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	float ForwardThrow = FVector::DotProduct(TankDirection, AIForwardIntention);
	float RightThrow = FVector::CrossProduct(TankDirection, AIForwardIntention).Z;

	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow);
}
