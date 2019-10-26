// Fill out your copyright notice in the Description page of Project Settings.

#include "Asteroid.h"
#include "Ship.h"
#include "AsteroidsCloneGameState.h"

#include "Classes/GameFramework/ProjectileMovementComponent.h"


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


// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector MoveDelta = MoveDirection * MoveScale;

    AddActorWorldOffset(MoveDelta, true, nullptr, ETeleportType::TeleportPhysics);

    WrapAroundWorld();

}

void AAsteroid::OnShipHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    AShip* Ship = Cast<AShip>(OtherActor);
    if (Ship != nullptr)
    {
        if (ShipClass != nullptr)
        {
            Ship->Destroy();
            AAsteroidsCloneGameState* GameState = Cast<AAsteroidsCloneGameState>(GetWorld()->GetGameState());
            if (GameState)
            {
                GameState->PlayerLives--;
            }
            GetWorld()->GetTimerManager().SetTimer(SpawnDelayHandle, this, &AAsteroid::SpawnShip, 3.0f, false);
        }
        
    }
}


// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
    OnActorHit.AddDynamic(this, &AAsteroid::OnShipHit);

    AsteroidRandomMovement();
}

void AAsteroid::AsteroidRandomMovement()
{
    float RandomDegrees = FMath::FRandRange(0.0f, 360.0f);
    float RandomX = FMath::Cos(FMath::DegreesToRadians(RandomDegrees));
    float RandomY = FMath::Sin(FMath::DegreesToRadians(RandomDegrees));

    MoveDirection = FVector(RandomX, RandomY, 0.0f);
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


void AAsteroid::WrapAroundWorld()
{
    AAsteroidsCloneGameState* GameState = Cast<AAsteroidsCloneGameState>(GetWorld()->GetGameState());
    FVector Location = GetActorLocation();
    bool bUpdateLocation = false;

    if (Location.X < -GameState->AsteroidWorldSizeX) {
        Location.X = GameState->AsteroidWorldSizeX;
        bUpdateLocation = true;
    }
    else if (Location.X > GameState->AsteroidWorldSizeX) {
        Location.X = -GameState->AsteroidWorldSizeX;
        bUpdateLocation = true;
    }

    if (Location.Y < -GameState->AsteroidWorldSizeY) {
        Location.Y = GameState->AsteroidWorldSizeY;
        bUpdateLocation = true;
    }
    else if (Location.Y > GameState->AsteroidWorldSizeY) {
        Location.Y = -GameState->AsteroidWorldSizeY;
        bUpdateLocation = true;
    }

    if (bUpdateLocation) {
        SetActorLocation(Location);
    }
}