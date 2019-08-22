// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocket.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Asteroid.h"
#include "LargeAsteroid.h"
#include "MediumAsteroid.h"
#include "SmallAsteroid.h"
#include "AsteroidsCloneGameModeBase.h"

// Sets default values
ARocket::ARocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketMesh");
    RocketMesh->SetConstraintMode(EDOFMode::XYPlane);

	SetRootComponent(RocketMesh);

	RocketMovement = CreateDefaultSubobject<UProjectileMovementComponent>("RocketMovement");
	RocketMovement->InitialSpeed = 1000.0f;
	RocketMovement->MaxSpeed = 1000.0f;
	RocketMovement->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
    OnActorHit.AddDynamic(this, &ARocket::OnRocketHit);

    RocketOriginalLocation = GetActorLocation();
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector RocketCurrentLocation = GetActorLocation();
    RocketDistance = FVector::Dist(RocketCurrentLocation, RocketOriginalLocation);
    if (RocketDistance >= 300.0f)
        Destroy();

}

void ARocket::OnRocketHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    ALargeAsteroid* LargeAsteroid = Cast<ALargeAsteroid>(OtherActor);
    if (LargeAsteroid != nullptr)
    {

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.bNoFail = true;

        FTransform AsteroidSpawnTransform;

        FVector RightNormal = GetActorRightVector();
        FVector RightVelocity = RightNormal * 100.0f;
        FVector AsteroidLocation = LargeAsteroid->GetActorLocation();

        if (MediumAsteroidClass) {
            AsteroidSpawnTransform.SetLocation(AsteroidLocation + RightVelocity);
            AsteroidSpawnTransform.SetRotation(LargeAsteroid->GetActorRotation().Quaternion());
            AsteroidSpawnTransform.SetScale3D(FVector::OneVector);
            GetWorld()->SpawnActor<AMediumAsteroid>(MediumAsteroidClass, AsteroidSpawnTransform, SpawnParams);

            AsteroidSpawnTransform.SetLocation(AsteroidLocation - RightVelocity);
            GetWorld()->SpawnActor<AMediumAsteroid>(MediumAsteroidClass, AsteroidSpawnTransform, SpawnParams);
        }

        LargeAsteroid->Destroy();

        Destroy();

        if (AAsteroidsCloneGameModeBase* GM = Cast<AAsteroidsCloneGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GM->OnRocketHit(20);
        }

    }

    AMediumAsteroid* MediumAsteroid = Cast<AMediumAsteroid>(OtherActor);
    if (MediumAsteroid != nullptr) {

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.bNoFail = true;

        FTransform AsteroidSpawnTransform;

        FVector RightNormal = GetActorRightVector();
        FVector RightVelocity = RightNormal * 80.0f;
        FVector AsteroidLocation = MediumAsteroid->GetActorLocation();

        if (SmallAsteroidClass) {
            AsteroidSpawnTransform.SetLocation(AsteroidLocation + RightVelocity);
            AsteroidSpawnTransform.SetRotation(MediumAsteroid->GetActorRotation().Quaternion());
            AsteroidSpawnTransform.SetScale3D(FVector::OneVector);
            GetWorld()->SpawnActor<ASmallAsteroid>(SmallAsteroidClass, AsteroidSpawnTransform, SpawnParams);

            AsteroidSpawnTransform.SetLocation(AsteroidLocation - RightVelocity);
            GetWorld()->SpawnActor<ASmallAsteroid>(SmallAsteroidClass, AsteroidSpawnTransform, SpawnParams);
        }

        MediumAsteroid->Destroy();

        Destroy();

        if (AAsteroidsCloneGameModeBase* GM = Cast<AAsteroidsCloneGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GM->OnRocketHit(50);
        }
    }

    ASmallAsteroid* SmallAsteroid = Cast<ASmallAsteroid>(OtherActor);
    if (SmallAsteroid != nullptr) {
        SmallAsteroid->Destroy();

        Destroy();
        
        if (AAsteroidsCloneGameModeBase* GM = Cast<AAsteroidsCloneGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GM->OnRocketHit(100);
        }
    }

}

