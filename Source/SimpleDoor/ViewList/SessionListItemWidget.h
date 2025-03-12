// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SessionListItemData.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SessionListItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEDOOR_API USessionListItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SessionNameText;
	void SetItemSelected(bool IsSelected);
};
