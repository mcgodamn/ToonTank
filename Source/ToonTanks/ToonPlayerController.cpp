// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonPlayerController.h"

void AToonPlayerController::SetPlayerControllerEnableState(bool Enable)
{
    if (Enable && GetPawn())
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = Enable;
}