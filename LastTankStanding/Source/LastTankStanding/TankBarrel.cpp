// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float DeltaRotation)
{
	float NewElevation = RelativeRotation.Pitch + (DeltaRotation * RelativeRotationSpeed * GetWorld()->DeltaTimeSeconds);

	NewElevation = FMath::Clamp<float>(NewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(NewElevation, 0.0f, 0.0f));
}
