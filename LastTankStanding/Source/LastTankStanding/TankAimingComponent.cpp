// Fill out your copyright notice in the Description page of Project Settings.

#include "LastTankStanding.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


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

	AmmoCount = StartingAmmoCount;
	LastFireTime = FPlatformTime::Seconds();
}

// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (AmmoCount == 0)
	{
		FiringStatus = EFiringStatus::Empty;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSecs)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

void UTankAimingComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret)
{
	TankBarrel = Barrel;
	TankTurret = Turret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(TankBarrel && TankTurret))
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel and/or turet not attached to Tank Aiming Component."))
		return;
	}

	FString OwnerName = GetOwner()->GetName();
	FVector ProjectileVelocity = FVector();

	FVector ProjectileStartPosition = TankBarrel->GetSocketLocation(FName("Projectile"));

	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
								this,
								ProjectileVelocity,
								ProjectileStartPosition,
								HitLocation,
								ProjectileSpeed,
								false,
								0.0f,
								0.0f,
								ESuggestProjVelocityTraceOption::DoNotTrace
						   );

	if (HaveAimSolution)
	{
		CurrentAimDirection = ProjectileVelocity.GetSafeNormal();
		MoveBarrel(CurrentAimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus == EFiringStatus::Aiming || FiringStatus == EFiringStatus::Locked)
	{
		AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
											ProjectileBlueprint,
											TankBarrel->GetSocketLocation("Projectile"),
											TankBarrel->GetSocketRotation("Projectile")
										 );
		SpawnedProjectile->LaunchProjectile(ProjectileSpeed);
		if (AmmoCount > 0)
			AmmoCount--;
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(TankTurret && TankBarrel))
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel and/or turet not attached to Tank Aiming Component."))
		return;
	}

	FRotator AimDirectionRotator = AimDirection.Rotation();
	FRotator TurretRotator = TankTurret->GetForwardVector().Rotation();
	FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	FRotator DeltaRotationTurret = AimDirectionRotator - TurretRotator;
	FRotator DeltaRotationBarrel = AimDirectionRotator - BarrelRotator;

	if (FMath::Abs(DeltaRotationTurret.Yaw) > 180.0f)
	{
		TankTurret->Rotate(-DeltaRotationTurret.Yaw);
	}
	else
	{
		TankTurret->Rotate(DeltaRotationTurret.Yaw);
	}
	TankBarrel->Elevate(DeltaRotationBarrel.Pitch);
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(TankBarrel)) { return false; }
	return !TankBarrel->GetForwardVector().Equals(CurrentAimDirection, 0.01f);
}
