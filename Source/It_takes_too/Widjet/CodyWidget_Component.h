// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../It_takes_too.h"
#include "Components/WidgetComponent.h"
#include "CodyWidget_Component.generated.h"

/**
 * 
 */
UCLASS()
class IT_TAKES_TOO_API UCodyWidget_Component : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UCodyWidget_Component();

protected:
	void InitWidget();

public:
	void SetNewLevel(int32 NewLevel);

private:
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true)) // Transient : 직렬화에서 제외
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 NumOfNail;

	struct FPlayerDataTable* CurrentStatData = nullptr;
};
