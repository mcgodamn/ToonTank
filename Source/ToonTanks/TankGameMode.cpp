// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "BasePawn.h"
#include "ToonPlayerController.h"
#include "TimerManager.h"

void ATankGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void ATankGameMode::ActorDied(AActor* DeadActor)
{
    if (auto pawn = Cast<ABasePawn>(DeadActor))
    {
        pawn->HandleDestruction();
    }

    if (Tank == Cast<ATank>(DeadActor) && ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerControllerEnableState(false);
    }
}

void ATankGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    ToonTanksPlayerController->SetPlayerControllerEnableState(false);

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(
        TimerHandle,
        FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonPlayerController::SetPlayerControllerEnableState, true),
        StartDelay,
        false
    );
}