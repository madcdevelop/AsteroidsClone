// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerShipController.h"

void APlayerShipController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeUIOnly());
}

