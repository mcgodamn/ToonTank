// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, Category = "Variable")
	float FireRange = 5;
	UPROPERTY(EditAnywhere, Category = "Variable")
	float FireRate = 5;

	bool InRange();
	void CheckFireCondition();
	FTimerHandle FireRateTimerHandle;
};
