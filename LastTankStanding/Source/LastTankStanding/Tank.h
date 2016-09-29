// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class LASTTANKSTANDING_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileSpeed = 100000.0f;

	// Makes the tank aim at the line traced hit location.
	void AimAt(FVector HitLocation);

	// Fires a projectile.
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void Fire();

	// Sets the barrel reference to the tank's aiming component.
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* Barrel);

	// Sets the turret reference to the tank's aiming component.
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* Turret);

protected:
	UTankAimingComponent* AimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* TankBarrel = nullptr;

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
