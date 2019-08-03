// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocket.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Asteroid.h"

// Sets default values
ARocket::ARocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketMesh");

	SetRootComponent(RocketMesh);

	RocketMovement = CreateDefaultSubobject<UProjectileMovementComponent>("RocketMovement");
	RocketMovement->InitialSpeed = 1000.0f;
	RocketMovement->MaxSpeed = 1000.0f;
	RocketMovement->ProjectileGravityScale = 0.0f;

	OnActorHit.AddDynamic(this, &ARocket::OnRocketHit);

}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(0.5f);
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARocket::OnRocketHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (AAsteroid* Asteroid = Cast<AAsteroid>(OtherActor))
	{
		Asteroid->Destroy();
		Destroy();
	}
}

