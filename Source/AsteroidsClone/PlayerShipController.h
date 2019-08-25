// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerShipController.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDSCLONE_API APlayerShipController : public APlayerController
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;
	
};
