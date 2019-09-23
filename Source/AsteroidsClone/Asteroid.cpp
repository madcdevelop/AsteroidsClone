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
    AsteroidMesh->SetEnableGravity(false);

    AsteroidMovement = CreateDefaultSubobject<UProjectileMovementComponent>("AsteroidMovement");
    AsteroidMovement->ProjectileGravityScale = 0.0f;

	SetRootComponent(AsteroidMesh);

    MoveScale = 2.0f;

}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
    OnActorHit.AddDynamic(this, &AAsteroid::OnShipHit);

    RandomX = RandomUnitNumber();
    RandomY = RandomUnitNumber();

    MoveDirection = FVector(RandomX, RandomY, 0.0f);
	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector MoveDelta = MoveDirection * MoveScale;

    AddActorWorldOffset(MoveDelta, true, nullptr, ETeleportType::TeleportPhysics);

}

void AAsteroid::OnShipHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    AShip* Ship = Cast<AShip>(OtherActor);
    if (Ship != nullptr)
    {
        
        if (ShipClass != nullptr)
        {

            Ship->Destroy();

            GetWorld()->GetTimerManager().SetTimer(SpawnDelayHandle, this, &AAsteroid::SpawnShip, 3.0f, false);
            
        }
        
    }
}

void AAsteroid::SpawnShip()
{
    FActorSpawnParameters ShipSpawnParams;
    ShipSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    ShipSpawnParams.bNoFail = true;

    FTransform ShipSpawnTransform;

    ShipSpawnTransform.SetLocation(FVector(0.0f, 0.0f, 190.0f));
    ShipSpawnTransform.SetRotation(FRotator(0.0f, 0.0f, 0.0f).Quaternion());
    ShipSpawnTransform.SetScale3D(FVector::OneVector);
            
    GetWorld()->SpawnActor<AShip>(ShipClass, ShipSpawnTransform, ShipSpawnParams);

    GetWorldTimerManager().ClearTimer(SpawnDelayHandle);
}

float AAsteroid::RandomUnitNumber()
{
    bool bRandom = FMath::RandBool();

    if (bRandom == true)
        return 1.0f;
    else
        return -1.0f;
}



