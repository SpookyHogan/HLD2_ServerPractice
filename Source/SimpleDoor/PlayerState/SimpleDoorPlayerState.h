// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SimpleDoorPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEDOOR_API ASimpleDoorPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
    int32 FragCount;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
    int32 EliminationCount;

    void AddFrag();

    //UFUNCTION(Server, Reliable)
    //void Server_AddFrag();

    void AddElimination();
	
    //UFUNCTION(Server, Reliable)
    //void Server_AddElimination();


    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
