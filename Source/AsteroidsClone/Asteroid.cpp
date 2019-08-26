// Fill out your copyright notice in the Description page of Project Settings.

#include "Asteroid.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Ship.h"


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
    OnActorHit.AddDynamic(this, &AAsteroid::OnShipHit);

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

void AAsteroid::OnShipHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    AShip* Ship = Cast<AShip>(OtherActor);
    if (Ship != nullptr)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        SpawnParams.bNoFail = true;

        FTransform ShipSpawnTransform;
        FTimerHandle UnusedHandle;

        if (ShipClass != nullptr)
        {
            Ship->Destroy();

            ShipSpawnTransform.SetLocation(FVector(0.0f,0.0f,190.0f));
            ShipSpawnTransform.SetRotation(FRotator(0.0f, 0.0f, 0.0f).Quaternion());
            ShipSpawnTransform.SetScale3D(FVector::OneVector);

            //GetWorldTimerManager().SetTimer(UnusedHandle, this, &AShip::TimerElapsed, TimerDelay, false);

            GetWorld()->SpawnActor<AShip>(ShipClass, ShipSpawnTransform, SpawnParams);
        }
        
    }
}



