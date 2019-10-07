// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "Rocket.h"
#include "AsteroidsCloneGameState.h"

#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
    FloatingPawnMovement->MaxSpeed = 2000.0f;
    FloatingPawnMovement->Acceleration = 500.0f;
    FloatingPawnMovement->Deceleration = 150.0f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    StaticMesh->SetConstraintMode(EDOFMode::XYPlane);

	SetRootComponent(StaticMesh);

	bUseControllerRotationYaw = true;
    RocketSpawnDelta = 60.0f;
}


// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    WrapAroundWorld();
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShip::Shoot);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShip::MoveForward);
	PlayerInputComponent->BindAxis("RotateLeft", this, &AShip::RotateLeft);
	PlayerInputComponent->BindAxis("RotateRight", this, &AShip::RotateRight);

}


// Called when the game starts or when spawned.
void AShip::BeginPlay()
{
	Super::BeginPlay();

    // Allow player to move on spawn without being destroyed right away
    SetActorEnableCollision(false);
    GetWorld()->GetTimerManager().SetTimer(CollisionSpawnTimerHandle, this, &AShip::EnableCollision, 3.0f, false);

}

void AShip::EnableCollision()
{
    SetActorEnableCollision(true);
    GetWorldTimerManager().ClearTimer(CollisionSpawnTimerHandle);
}

void AShip::MoveForward(float Amount) 
{
    float ShipAcceleration = FloatingPawnMovement->Acceleration;
	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * Amount * ShipAcceleration);
}

void AShip::RotateLeft(float Amount)
{
	AddControllerYawInput(Amount);
}

void AShip::RotateRight(float Amount)
{
	AddControllerYawInput(Amount);
}

void AShip::Shoot()
{
	if (RocketClass != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;

		FTransform RocketSpawnTransform;
		RocketSpawnTransform.SetLocation(GetActorForwardVector() * RocketSpawnDelta + GetActorLocation());
		RocketSpawnTransform.SetRotation(GetActorRotation().Quaternion());
		RocketSpawnTransform.SetScale3D(FVector(1.0f));

		GetWorld()->SpawnActor<ARocket>(RocketClass, RocketSpawnTransform, SpawnParams);
	}
}


void AShip::WrapAroundWorld()
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