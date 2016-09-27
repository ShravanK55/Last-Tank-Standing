// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class LASTTANKSTANDING_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileSpeed = 100000.0f;

	// Makes the tank aim at the line traced hit location.
	void AimAt(FVector HitLocation);

	// Sets the barrel reference to the tank's aiming component.
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* Barrel);

protected:
	UTankAimingComponent* AimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
};
