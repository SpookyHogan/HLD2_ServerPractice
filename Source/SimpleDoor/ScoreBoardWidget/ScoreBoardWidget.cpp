// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreBoardWidget.h"
#include "ScoreBoardListItemData.h"
#include "Components/ListView.h"
#include "SimpleDoorPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h" 

void UScoreBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResizeImage();
	
}

void UScoreBoardWidget::RefreshScoreboard()
{
	if (ScoreBoardListView)
	{
		ScoreBoardListView->ClearListItems();
		AGameStateBase* GState = GetWorld()->GetGameState<AGameStateBase>();
		for (APlayerState* PState : GState->PlayerArray)
		{
			if (PState)
			{
				UScoreBoardListItemData* NewScoreBoardItem = NewObject<UScoreBoardListItemData>();
				if (NewScoreBoardItem)
				{
					ASimpleDoorPlayerState* SimpleDoorState = Cast<ASimpleDoorPlayerState>(PState);
					if (SimpleDoorState)
					{
						NewScoreBoardItem->PlayerStateName = SimpleDoorState->GetName();
						NewScoreBoardItem->PlayerName = SimpleDoorState->GetPlayerName();
						NewScoreBoardItem->Frags = FString::FromInt(SimpleDoorState->FragCount);
						NewScoreBoardItem->Eliminations = FString::FromInt(SimpleDoorState->EliminationCount);
						ScoreBoardListView->AddItem(NewScoreBoardItem);
					}
				}
			}
		}
	}
}

void UScoreBoardWidget::ResizeImage()
{
	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);

	FVector2D NewSize = ViewportSize * 0.8f;

	Image->SetRenderScale(FVector2D(NewSize.X / ViewportSize.X, NewSize.Y / ViewportSize.Y));
}



