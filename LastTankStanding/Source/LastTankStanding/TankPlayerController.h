// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


UCLASS()
class LASTTANKSTANDING_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.4f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

private:
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector& LookDirection, FVector2D ScreenLocation) const;
	bool GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const;
};
