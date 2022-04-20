// Fill out your copyright notice in the Description page of Project Settings.


#include "Cody_Widget.h"
#include "Crosshair_Widget.h"
#include "Nail_Count_Widget.h"
#include "../Character/Actor_CodyCh.h"

void UCody_Widget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	Aim.BindUFunction(this, FName("Fuc_StartAim"));
	EndAim.BindUFunction(this, FName("Fuc_EndAim"));

	ListenForInputAction(TEXT("Aim"), IE_Pressed, false, Aim);
	ListenForInputAction(TEXT("Aim"), IE_Released, false, EndAim);
}


void UCody_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UCody_Widget::Fuc_StartAim()
{
	UE_LOG(LogTemp, Warning, TEXT("StartAim"));
	SetVisibility(ESlateVisibility::Visible);
}

void UCody_Widget::Fuc_EndAim() {
	UE_LOG(LogTemp, Warning, TEXT("EndAim"));
	SetVisibility(ESlateVisibility::Hidden);
}

void UCody_Widget::NailIn()
{
}

void UCody_Widget::NailOut()
{
}

