// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UseInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLEDOOR_API IUseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Use();

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void Use(APlayerController* PC);
};
