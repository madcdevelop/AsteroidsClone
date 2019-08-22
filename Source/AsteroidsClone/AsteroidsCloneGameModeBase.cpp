// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidsCloneGameModeBase.h"
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

void AAsteroidsCloneGameModeBase::OnRocketHit(int32 pointsEarned)
{
    AAsteroidsCloneGameState* GS = Cast<AAsteroidsCloneGameState>(GameState);
    if (GS != nullptr) 
    {
        GS->Points += pointsEarned;

        if (GEngine != nullptr) {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("You scored %d points. you now have %d points"), pointsEarned, GS->Points));
        }
    
    }
}
