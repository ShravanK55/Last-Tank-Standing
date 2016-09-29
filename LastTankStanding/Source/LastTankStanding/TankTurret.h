// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LASTTANKSTANDING_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float DeltaRotation);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float RelativeRotationSpeed = 2.0f;
};
