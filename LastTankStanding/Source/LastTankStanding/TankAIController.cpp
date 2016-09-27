// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
	if (ControlledTank != nullptr)
	{
		if (PlayerTank != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s aims at %s."), *(ControlledTank->GetName()) ,*(PlayerTank->GetName()))
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController is not possessing anything."), *(ControlledTank->GetName()))
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	if (!GetControlledTank()) { return; }

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		// TODO: Move towards the player.

		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
