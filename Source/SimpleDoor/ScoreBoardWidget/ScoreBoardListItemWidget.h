// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ScoreBoardListItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEDOOR_API UScoreBoardListItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerNameText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FragsText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EliminationsText;
};
