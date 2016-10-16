// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
class UTankAimingComponent;

UCLASS()
class LASTTANKSTANDING_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float CrosshairLocationX = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrosshairLocationY = 0.4f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundControlledTank(ATank* TankRef);

private:
	UTankAimingComponent* AimingComponent = nullptr;

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector& LookDirection, FVector2D ScreenLocation) const;
	bool GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const;
};
