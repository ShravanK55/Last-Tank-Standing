// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class LASTTANKSTANDING_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Makes the tank aim at the line traced hit location.
	void AimAt(FVector HitLocation);

	// Fires a projectile from the tank's barrel.
	void Fire();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Components")
	UTankAimingComponent* AimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
