// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Bullet.h"
#include "HPComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	bulletSpwanPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Point"));
	bulletSpwanPoint->SetupAttachment(TurretMesh);
	
	HPComponent = CreateDefaultSubobject<UHPComponent>(TEXT("HP Component"));
}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator Rotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), Rotation, GetWorld()->DeltaTimeSeconds, 25.f));
}

void ABasePawn::Fire()
{
	auto bullet = GetWorld()->SpawnActor<ABullet>(
		BulletObject, bulletSpwanPoint->GetComponentLocation(), bulletSpwanPoint->GetComponentRotation());
	bullet->SetOwner(this);

}

void ABasePawn::HandleDestruction()
{
	if (OnDieParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, OnDieParticle, GetActorLocation(), GetActorRotation());
	}
	UGameplayStatics::PlaySoundAtLocation(this, DeadSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeadCameraShake);
}