// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "BasePawn.h"

void ATankGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATankGameMode::ActorDied(AActor* DeadActor)
{
    if (auto pawn = Cast<ABasePawn>(DeadActor))
    {
        pawn->HandleDestruction();
    }

    if (Tank == Cast<ATank>(DeadActor) && Tank->GetPlayerController())
    {
        Tank->DisableInput(Tank->GetPlayerController());
    }
}