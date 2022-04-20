// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cody_Widget.generated.h"
/**
 * 
 */
UCLASS()
class IT_TAKES_TOO_API UCody_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnInputAction Aim;
	FOnInputAction EndAim;

private:
	uint8 NumOfNail;
	bool IsAimed;
private:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;		// beginplay 같은 친구

	UPROPERTY(Meta = (BindWidget)) class UCrosshair_Widget* CrossHair;
	UPROPERTY(Meta = (BindWidget)) class UUserWidget* BattleWidget;
	
	UFUNCTION()
	void Fuc_StartAim();

	UFUNCTION()
	void Fuc_EndAim();
	void NailIn();
	void NailOut();
};
