// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

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
	
	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

	// Aim at the specified hit location.
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void AimAt(FVector HitLocation);

	// Fires a projectile.
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ProjectileSpeed = 100000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSecs = 3.0f;

	double LastFireTime = 0.0f;

	FVector CurrentAimDirection = FVector();

	UTankBarrel* TankBarrel = nullptr;
	UTankTurret* TankTurret = nullptr;

	// Moves the barrel in the required aim direction.
	void MoveBarrel(FVector AimDirection);

	// Checks if the barrel is still moving.
	bool IsBarrelMoving() const;
};
