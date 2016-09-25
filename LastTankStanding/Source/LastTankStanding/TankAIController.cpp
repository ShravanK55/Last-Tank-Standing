// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankAIController.h"


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

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
