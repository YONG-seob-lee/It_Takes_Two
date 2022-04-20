// Fill out your copyright notice in the Description page of Project Settings.


#include "Nail_Count_Widget.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include"Animation/WidgetAnimation.h"

void UNail_Count_Widget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UNail_Count_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNail_Count_Widget::FillAnimationsMap()
{
	Nailin_1->GetBindings();
	//Cast<UCanvasPanelSlot>(Nail_1->Slot)->
}

void UNail_Count_Widget::NailInAnim1()
{
	PlayAnimation(Nailin_1);
}

void UNail_Count_Widget::NailInAnim2()
{
	PlayAnimation(Nailin_2);
}

void UNail_Count_Widget::NailInAnim3()
{
	PlayAnimation(Nailin_3);
}

void UNail_Count_Widget::NailOutAnim1()
{
	PlayAnimation(Nailout_1);	
}

void UNail_Count_Widget::NailOutAnim2()
{
	PlayAnimation(Nailout_2);
}

void UNail_Count_Widget::NailOutAnim3()
{
	PlayAnimation(Nailout_3);
}
