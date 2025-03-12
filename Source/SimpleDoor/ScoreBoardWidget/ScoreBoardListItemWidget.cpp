// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreBoardListItemWidget.h"
#include "ScoreBoardListItemData.h"
#include "Components/TextBlock.h"

void UScoreBoardListItemWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UScoreBoardListItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    UScoreBoardListItemData* ScoreBoardData = Cast<UScoreBoardListItemData>(ListItemObject);
    if (ScoreBoardData)
    {
        if (PlayerNameText)
        {
            PlayerNameText->SetText(FText::FromString(ScoreBoardData->PlayerName));
            PlayerNameText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f)));

            if (ScoreBoardData->PlayerStateName == GetWorld()->GetFirstPlayerController()->PlayerState.GetName())
            {
                PlayerNameText->SetColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)));
            }
        }

        if (FragsText)
        {
            FragsText->SetText(FText::FromString(ScoreBoardData->Frags));
        }

        if (EliminationsText)
        {
            EliminationsText->SetText(FText::FromString(ScoreBoardData->Eliminations));
        }
    }
}
