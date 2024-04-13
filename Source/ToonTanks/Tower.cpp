// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATank* Tank;

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (InRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

bool ATower::InRange()
{
    return Tank && FVector::Dist(Tank->GetActorLocation(), GetActorLocation()) <= FireRange;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if (InRange() && Tank->IsAlive())
    {
        Fire();
    }
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
    
    Destroy();
}