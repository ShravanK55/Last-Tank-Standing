// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float DeltaRotation)
{
	float NewRotation = RelativeRotation.Yaw + (DeltaRotation * RelativeRotationSpeed * GetWorld()->DeltaTimeSeconds);

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}
