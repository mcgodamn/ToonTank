// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATank* Tank;

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (Tank)
    {
        auto distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
        if (distance < FireRange)
        {
            RotateTurret(Tank->GetActorLocation());
        }
    }
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
    
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}