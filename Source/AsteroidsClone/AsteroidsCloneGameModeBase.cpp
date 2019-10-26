// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidsCloneGameModeBase.h"
#include "AsteroidsClone.h"
#include "Ship.h"

#include "UObject/ConstructorHelpers.h"
#include "AsteroidsCloneGameState.h"

AAsteroidsCloneGameModeBase::AAsteroidsCloneGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Ship"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}


void AAsteroidsCloneGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

void AAsteroidsCloneGameModeBase::OnRocketHit(int32 pointsEarned)
{
    AAsteroidsCloneGameState* GS = Cast<AAsteroidsCloneGameState>(GameState);
    if (GS != nullptr) 
    {
        GS->AddPoints(pointsEarned);
    }
}


void AAsteroidsCloneGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    ChangeMenuWidget(StartingWidgetClass);
}