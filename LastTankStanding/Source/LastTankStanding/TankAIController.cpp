// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* TankAimingComponent = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
	if (TankAimingComponent)
	{
		AimingComponent = TankAimingComponent;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming component is still not created in the tank!"))
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->DeathEvent.AddUniqueDynamic(this, &ATankAIController::OnDeath);
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (!ensure(ControlledTank)) { return; }

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank && ensure(AimingComponent))
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		{
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s died!"), *GetPawn()->GetName())
}
