// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	AimingComponent->AimAt(HitLocation, ProjectileSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* Barrel)
{
	if (AimingComponent)
	{
		AimingComponent->SetBarrelReference(Barrel);
	}
}

void ATank::SetTurretReference(UTankTurret* Turret)
{
	if (AimingComponent)
	{
		AimingComponent->SetTurretReference(Turret);
	}
}
