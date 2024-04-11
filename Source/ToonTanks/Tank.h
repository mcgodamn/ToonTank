// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ATank();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void HandleDestruction() override;

	class APlayerController* GetPlayerController() const { return PlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Comp")
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Comp")
	class UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, Category = "Variable")
	float Speed = 1;
	UPROPERTY(EditAnywhere, Category = "Variable")
	float TurnRate = 1;
	
	class APlayerController* PlayerController;

	void Move(float Value);
	void Turn(float Value);
};
