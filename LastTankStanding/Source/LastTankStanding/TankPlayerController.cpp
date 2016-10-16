// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* TankAimingComponent = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
	if (TankAimingComponent)
	{
		AimingComponent = TankAimingComponent;
		FoundAimingComponent(TankAimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming component is still not created in the tank!"))
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->DeathEvent.AddUniqueDynamic(this, &ATankPlayerController::OnDeath);
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!Cast<ATank>(GetPawn())) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation) && ensure(AimingComponent)) // This method will perform a line trace.
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D AimLocation = FVector2D(ViewportSizeX * CrosshairLocationX, ViewportSizeY * CrosshairLocationY);

	FVector LookDirection;
	if (GetLookDirection(LookDirection, AimLocation))
	{
		return GetLookVectorHitLocation(HitLocation, LookDirection);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection, FVector2D ScreenLocation) const
{
	FVector CameraLocation; // Discarding this value, not needed.
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0f);
	return false;
}

void ATankPlayerController::OnDeath()
{
	if (GetPawn())
	{
		StartSpectatingOnly();
	}
}
