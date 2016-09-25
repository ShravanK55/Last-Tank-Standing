// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing %s."), *(ControlledTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController is not possessing anything."), *(ControlledTank->GetName()))
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) // This method will perform a line trace.
	{
		UE_LOG(LogTemp, Warning, TEXT("%s aims at %s"), *(GetControlledTank()->GetName()), *(HitLocation.ToString()))

		// TODO: Make the tank aim at the point.
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0f, 1.0f, 1.0f);
	return true;
}