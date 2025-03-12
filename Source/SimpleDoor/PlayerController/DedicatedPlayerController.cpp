// Fill out your copyright notice in the Description page of Project Settings.


#include "DedicatedPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BasicCharacter.h"
#include "SimpleDoorGameInstance.h"
#include "SimpleDoorPlayerState.h"
#include "ScoreBoardWidget.h"
#include "GameFramework/GameStateBase.h"



void ADedicatedPlayerController::OnPossess(APawn* PossesedPawn)
{
    Super::OnPossess(PossesedPawn);
    MC_EnableInput();
}

void ADedicatedPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{
    Super::AcknowledgePossession(PossesedPawn);
    PossessedPawn = Cast<ABasicCharacter>(PossesedPawn);
    InitName();
}

void ADedicatedPlayerController::MC_EnableInput_Implementation()
{
    EnableInput(this);
}

void ADedicatedPlayerController::OnUnPossess()
{
    Super::OnUnPossess();
    PossessedPawn = nullptr;
}

void ADedicatedPlayerController::BeginPlay()
{
    Super::BeginPlay();
    //Add Input Mapping Context
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    if (ScoreboardWidgetClass && IsLocalPlayerController())//if scoreboard exists and is an actual "human" player
    {
        ScoreboardWidget = CreateWidget< UScoreBoardWidget>(this, ScoreboardWidgetClass);
        if (ScoreboardWidget)
        {
            ScoreboardWidget->AddToViewport();
            ScoreboardWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }

}

void ADedicatedPlayerController::ShowScoreBoard()
{
    if (ScoreboardWidget)
    {
        ScoreboardWidget->RefreshScoreboard();
        ScoreboardWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void ADedicatedPlayerController::HideScoreBoard()
{
    if (ScoreboardWidget)
    {
        ScoreboardWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ADedicatedPlayerController::InitName()
{
    USimpleDoorGameInstance* GameInstance = Cast<USimpleDoorGameInstance>(GetGameInstance());
    if (GameInstance && PlayerName.IsEmpty())
    {
        PlayerName = HandleDuplicateNames(GameInstance->GetPlayerName());

        Server_InitName(PlayerName);

    }
}

void ADedicatedPlayerController::Server_InitName_Implementation(const FString& newName)
{

        ASimpleDoorPlayerState* PState = GetPlayerState<ASimpleDoorPlayerState>();
        if (PState)
        {
            PState->SetPlayerName(newName);
        }

}

void ADedicatedPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADedicatedPlayerController::Move);
       
        // Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ADedicatedPlayerController::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADedicatedPlayerController::StopJumping);

        // Looking
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADedicatedPlayerController::Look);

        // Interact
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ADedicatedPlayerController::Interact);

        // Fire
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ADedicatedPlayerController::Fire);

        // ScoreBoard
        EnhancedInputComponent->BindAction(ScoreBoardAction, ETriggerEvent::Triggered, this, &ADedicatedPlayerController::ShowScoreBoard);
        EnhancedInputComponent->BindAction(ScoreBoardAction, ETriggerEvent::Completed, this, &ADedicatedPlayerController::HideScoreBoard);
    }
}

const FString ADedicatedPlayerController::HandleDuplicateNames(const FString& PName)
{
    FString FinalName;
    if (PlayerName.IsEmpty() && !PName.IsEmpty())
    {
        FinalName = PName;
        AGameStateBase* GameState = GetWorld()->GetGameState();
        if (!GameState)
        {
            return FinalName;
        }

        int32 NameCount = 0;

        for (APlayerState* PState : GameState->PlayerArray)
        {
            if (!PState)
                continue;

            if (PState && PState->GetPlayerName().StartsWith(FinalName))
            {
                NameCount++;
            }
        }

        ASimpleDoorPlayerState* PState = GetPlayerState<ASimpleDoorPlayerState>();
        if (PState)
        {
            if (NameCount > 0)
            {
                FinalName = FinalName + FString::Printf(TEXT("%d"), NameCount);
            }
        }
    }

    return FinalName;
}

void ADedicatedPlayerController::Move(const FInputActionValue& Value)
{
    if (PossessedPawn)
    {
        PossessedPawn->Move(Value);
    }
}

void ADedicatedPlayerController::Look(const FInputActionValue& Value)
{
    if (PossessedPawn)
    {
        PossessedPawn->Look(Value);
    }
}

void ADedicatedPlayerController::Jump(const FInputActionValue& Value)
{
    if (PossessedPawn)
    {
        PossessedPawn->Jump();
    }
}

void ADedicatedPlayerController::StopJumping(const FInputActionValue& Value)
{
    if (PossessedPawn)
    {
        PossessedPawn->StopJumping();
    }
}

void ADedicatedPlayerController::Interact()
{
    if (PossessedPawn)
    {
        PossessedPawn->Interact();
    }
}

void ADedicatedPlayerController::Fire()
{
    if (PossessedPawn)
    {
        PossessedPawn->Fire();
    }
}
