// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LASTTANKSTANDING_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float RotationSpeed = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = 0.0f;
};
