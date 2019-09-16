// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "Rocket.h"

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
    FloatingPawnMovement->Deceleration = 300.0f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    StaticMesh->SetConstraintMode(EDOFMode::XYPlane);

	SetRootComponent(StaticMesh);

	bUseControllerRotationYaw = true;

}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
    
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
		RocketSpawnTransform.SetLocation(GetActorForwardVector() * 100.0f + GetActorLocation());
		RocketSpawnTransform.SetRotation(GetActorRotation().Quaternion());
		RocketSpawnTransform.SetScale3D(FVector(1.0f));

		GetWorld()->SpawnActor<ARocket>(RocketClass, RocketSpawnTransform, SpawnParams);
	}
}


// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

