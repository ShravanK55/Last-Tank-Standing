// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASTTANKSTANDING_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Sets the barrel reference, so as to use it as a projectile's start point.
	void SetBarrelReference(UTankBarrel* Barrel);

	// Sets the turret reference in order to turn it in accordance with the player's aim.
	void SetTurretReference(UTankTurret* Turret);

	// Aim at the specified hit location.
	void AimAt(FVector HitLocation, float ProjectileSpeed);

private:
	UTankBarrel* TankBarrel = nullptr;
	UTankTurret* TankTurret = nullptr;

	// Moves the barrel in the required aim direction.
	void MoveBarrel(FVector AimDirection);
};
