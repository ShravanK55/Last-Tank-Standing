// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* Barrel)
{
	if (!Barrel) { return; }
	TankBarrel = Barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* Turret)
{
	if (!Turret) { return; }
	TankTurret = Turret;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float ProjectileSpeed)
{
	FString OwnerName = GetOwner()->GetName();
	FVector ProjectileStartLocation = FVector(), ProjectileVelocity = FVector();

	if (!TankBarrel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel not attached to Tank Aiming Component."))
		return;
	}

	if (!TankTurret)
	{
		UE_LOG(LogTemp, Warning, TEXT("Turret not attached to Tank Aiming Component."))
		return;
	}

	FVector ProjectileStartPosition = TankBarrel->GetSocketLocation(FName("Projectile"));

	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
								this,
								ProjectileVelocity,
								ProjectileStartLocation,
								HitLocation,
								ProjectileSpeed,
								false,
								0.0f,
								0.0f,
								ESuggestProjVelocityTraceOption::DoNotTrace
						   );

	if (HaveAimSolution)
	{
		FVector AimDirection = ProjectileVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator AimDirectionRotator = AimDirection.Rotation();
	FRotator TurretRotator = TankTurret->GetForwardVector().Rotation();
	FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	FRotator DeltaRotationTurret = AimDirectionRotator - TurretRotator;
	FRotator DeltaRotationBarrel = AimDirectionRotator - BarrelRotator;

	TankTurret->Rotate(DeltaRotationTurret.Yaw);
	TankBarrel->Elevate(DeltaRotationBarrel.Pitch);
}
