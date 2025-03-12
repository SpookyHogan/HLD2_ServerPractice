// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleDoorPlayerState.h"
#include "Net/UnrealNetwork.h"


void ASimpleDoorPlayerState::AddFrag()
{
    FragCount++;
}

void ASimpleDoorPlayerState::AddElimination()
{
    EliminationCount++;
}

void ASimpleDoorPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ASimpleDoorPlayerState, FragCount);
    DOREPLIFETIME(ASimpleDoorPlayerState, EliminationCount);
}
