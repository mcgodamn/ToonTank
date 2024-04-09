// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	void RotateTurret(FVector LookAtTarget);

private:
	UPROPERTY(VisibleAnywhere, Category = "Comp", BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, Category = "Comp", BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	class UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, Category = "Comp", BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	class UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, Category = "Comp", BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	class USceneComponent* bulletSpwanPoint;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
