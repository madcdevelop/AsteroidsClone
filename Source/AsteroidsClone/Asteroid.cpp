// Fill out your copyright notice in the Description page of Project Settings.

#include "Asteroid.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"


// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    AsteroidMesh->SetConstraintMode(EDOFMode::XYPlane);

	SetRootComponent(AsteroidMesh);

    //MoveScale = 200.0f;
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

    //MoveDirection = FMath::VRand();
	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //FVector MoveDelta = (MoveDirection * (FMath::Sin(GetWorld()->GetTimeSeconds() + DeltaTime)
    //    - FMath::Sin(GetWorld()->GetTimeSeconds()))) * MoveScale;

    //AddActorWorldOffset(MoveDelta, true);

}



