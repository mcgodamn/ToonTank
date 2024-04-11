// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/PlayerController.h>
#include <Camera/CameraComponent.h>
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineBaseTypes.h"

// Sets default values
ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

float NowDeltaLocation;
void ATank::Move(float Value)
{
	NowDeltaLocation = Value;

	auto DeltaLocation = FVector::ZeroVector;
	auto deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	DeltaLocation.X = Value * Speed * deltaTime;
	AddActorLocalOffset(DeltaLocation, true);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	if (PlayerController
		&& PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		RotateTurret(HitResult.ImpactPoint);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<APlayerController>(GetController());
}

void ATank::Turn(float Value)
{
	// if (NowDeltaLocation == 0) return;

	auto DeltaRotation = FRotator::ZeroRotator;
	auto deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaRotation.Yaw = Value * TurnRate * deltaTime * (NowDeltaLocation == -1 ? -1 : 1);
	AddActorLocalRotation(DeltaRotation, true);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}