// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/PlayerController.h>
#include <Camera/CameraComponent.h>
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

APlayerController* PlayerController;

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

	if (PlayerController)
	{
		FHitResult HitResult;
		if (PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility, false, HitResult))
		{
			DrawDebugSphere(
				GetWorld(), HitResult.ImpactPoint, 10, 12, FColor::Red);
		}
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
	if (NowDeltaLocation == 0) return;

	auto DeltaRotation = FRotator::ZeroRotator;
	auto deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaRotation.Yaw = Value * TurnRate * deltaTime;
	AddActorLocalRotation(DeltaRotation, true);
}