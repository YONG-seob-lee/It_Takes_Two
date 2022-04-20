// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPlayerController.h"
<<<<<<< HEAD
#include "../Widjet/Cody_Widget.h"
#include "../Character/Actor_CodyCh.h"
#include "Components/Image.h"

AFirstPlayerController::AFirstPlayerController()
{
	IsAimed = false;
	static ConstructorHelpers::FClassFinder<UCody_Widget> CODY_WIDGET(TEXT("/Game/Blueprints/Widget_BP/CodyWidget_BP.CodyWidget_BP_C"));
	if (CODY_WIDGET.Succeeded()) {
		UI_Class = CODY_WIDGET.Class;
	}
}
=======
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82

void AFirstPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
<<<<<<< HEAD
=======
	ABLOG_S(Warning);
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
}

void AFirstPlayerController::OnPossess(APawn* aPawn)
{
<<<<<<< HEAD
	Super::OnPossess(aPawn);
	if (UI_Class != nullptr) {
		CodyUI_Object = CreateWidget<UCody_Widget>(this, UI_Class);
		if (CodyUI_Object != nullptr) 
	 {
			CodyUI_Object->AddToViewport();
	//		CodyUI_Object->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AFirstPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//if (IsAimed)	CodyUI_Object->SetVisibility(ESlateVisibility::Visible);
	//else	CodyUI_Object->SetVisibility(ESlateVisibility::Hidden);
=======
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
}

void AFirstPlayerController::BeginPlay()
{
	Super::BeginPlay();
<<<<<<< HEAD
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AFirstPlayerController::GetBind(AActor_CodyCh* Target)
{
	Owner = Target;
}
=======

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
