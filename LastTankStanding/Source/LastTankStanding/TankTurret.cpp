// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float NewRotation = RelativeRotation.Yaw + (RelativeSpeed * RotationSpeed * GetWorld()->DeltaTimeSeconds);

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}
