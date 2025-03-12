// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScoreBoardListItemData.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEDOOR_API UScoreBoardListItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite)
	FString PlayerStateName;

	UPROPERTY(BlueprintReadWrite)
	FString Frags;

	UPROPERTY(BlueprintReadWrite)
	FString Eliminations;
};
