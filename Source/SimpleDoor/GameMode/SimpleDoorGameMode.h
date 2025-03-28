// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleDoorGameMode.generated.h"

UCLASS(minimalapi)
class ASimpleDoorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimpleDoorGameMode();
	void RespawnPlayer(AController* PlayerController);

	void OnPlayerFragged(AController* Fragger, AController* Victim);

	void BeginPlay() override;
protected:
	TArray<AActor*> PlayerStarts;
};



