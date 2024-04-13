// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	TrailParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	TrailParticleSystem->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetOwner() || !OtherActor || OtherActor == this || OtherActor == GetOwner())
	{
		Destroy();
		return;
	}
	
	auto controller = GetOwner()->GetInstigatorController();
	UGameplayStatics::ApplyDamage(OtherActor, Damage, controller, this, UDamageType::StaticClass());
	Destroy();

	if (OnHitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, OnHitParticle, GetActorLocation(), GetActorRotation());
	}
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
}