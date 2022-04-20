// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair_Widget.generated.h"

/**
 * 
 */
UCLASS()
class IT_TAKES_TOO_API UCrosshair_Widget : public UUserWidget
{
	GENERATED_BODY()

private:

private:
	void AA();

	UPROPERTY(Meta = (BindWidget)) class UImage* CrossHair_Circle;
	UPROPERTY(Meta = (BindWidget)) class UImage* CrossHair_Cross;
	
	//UPROPERTY(Meta = (BindWidget)) class UNail_Count_Widget* NailCount;

};
