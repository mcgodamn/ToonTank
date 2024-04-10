// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Comp", BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	class UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, Category = "Comp", BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, Category = "Variable")
	float Damage = 10;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
