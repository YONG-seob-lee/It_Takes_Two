// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Nail_Count_Widget.generated.h"

/**
 * 
 */
UCLASS()
class IT_TAKES_TOO_API UNail_Count_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	void FillAnimationsMap();
	uint8 NumOfNail;

private:
	UPROPERTY(Meta = (BindWidget)) class UImage* Nail_Inside1;		// 왼쪽부터 순서대로 1 ,2, 3 카운트
	UPROPERTY(Meta = (BindWidget)) class UImage* Nail_Inside2;
	UPROPERTY(Meta = (BindWidget)) class UImage* Nail_Inside3;
	UPROPERTY(Meta = (BindWidget)) class UImage* Nail_Outside1;		// 왼쪽부터 순서대로 1 ,2, 3 카운트
	UPROPERTY(Meta = (BindWidget)) class UImage* Nail_Outside2;
	UPROPERTY(Meta = (BindWidget)) class UImage* Nail_Outside3;


	UPROPERTY(Transient, Meta = (BindWidgetAnim), Meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* Nailin_1;
	UPROPERTY(Transient, Meta = (BindWidgetAnim), Meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* Nailin_2;
	UPROPERTY(Transient, Meta = (BindWidgetAnim), Meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* Nailin_3;
	UPROPERTY(Transient, Meta = (BindWidgetAnim), Meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* Nailout_1;
	UPROPERTY(Transient, Meta = (BindWidgetAnim), Meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* Nailout_2;
	UPROPERTY(Transient, Meta = (BindWidgetAnim), Meta = (AllowPrivateAccess = true))
	class UWidgetAnimation* Nailout_3;

public:
	void NailInAnim1();
	void NailInAnim2();
	void NailInAnim3();
	void NailOutAnim1();
	void NailOutAnim2();
	void NailOutAnim3();

};
