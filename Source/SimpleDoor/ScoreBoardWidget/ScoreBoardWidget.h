// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreBoardWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEDOOR_API UScoreBoardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;
	void RefreshScoreboard();


	UFUNCTION(BlueprintCallable)
	void ResizeImage();

	UPROPERTY(meta = (BindWidget))
	class UImage* Image;

	UPROPERTY(meta = (BindWidget))

	class UListView* ScoreBoardListView;

};
