// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	if (!LeftTrack || !RightTrack) { return; }
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tracks are not attached to the movement component!"))
	}
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tracks are not attached to the movement component!"))
	}
}
