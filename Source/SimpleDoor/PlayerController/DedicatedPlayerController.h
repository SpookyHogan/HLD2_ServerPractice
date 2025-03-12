// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DedicatedPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEDOOR_API ADedicatedPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ScoreBoardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))

	class UInputMappingContext* DefaultMappingContext;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	virtual void AcknowledgePossession(APawn* Pawn) override;
	UFUNCTION(NetMulticast, Reliable)
	void MC_EnableInput();

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void ShowScoreBoard();

	void HideScoreBoard();

	void InitName();

	UFUNCTION(Server, Reliable)
	void Server_InitName(const FString& newName);

	const FString HandleDuplicateNames(const FString& PName);

	/** Called for movement input */
	void Move(const struct FInputActionValue& Value);

	/** Called for looking input */
	void Look(const struct FInputActionValue& Value);

	/** Called for jump input */
	void Jump(const struct FInputActionValue& Value);

	/** Called for jump input */
	void StopJumping(const struct FInputActionValue& Value);

	/** Called for Interact input */
	void Interact();

	/** Called for Fire input */
	void Fire();

	class ABasicCharacter* PossessedPawn;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> ScoreboardWidgetClass;

	UPROPERTY()
	class UScoreBoardWidget* ScoreboardWidget;

	FString PlayerName;
	
};
