// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCh_AnimInst.h"
#include "../Character/Actor_Base_Character.h"
#include "../Character/Actor_CodyCh.h"

UBaseCh_AnimInst::UBaseCh_AnimInst()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RollAnimMontageFinder(TEXT("/Game/BaseCharacter/Animation/Montage/Roll_Montage.Roll_Montage"));
	if (RollAnimMontageFinder.Succeeded() == false)
		return;
	RollAnimMontageInstance = RollAnimMontageFinder.Object;

	CurrentPawnSpeed = 0.0f;
}

void UBaseCh_AnimInst::RollAnimMontage() {
	Montage_Play(RollAnimMontageInstance);
}


void UBaseCh_AnimInst::AnimNotify_RollEndCheck()
{

	UE_LOG(LogTemp, Warning, L"AnimNotify_RollEndCheck");
	AActor_Base_Character* Cody = Cast<AActor_Base_Character>(GetOwningActor());
	
	Cody->SetEndRoll();
}

void UBaseCh_AnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	AActor_Base_Character* Cody = Cast<AActor_Base_Character>(GetOwningActor());

	if (IsValid(Cody))
	{
		CurrentPawnSpeed = Cody->GetVelocity().Size();
		JogDirection = Cody->GetPressDirection();

		if (JogDirection != 0.0f)
		{
			JogDirection = Cody->GetPressDirection();	// Á¶±ë È®ÀÎ
		}
		State = Cody->GetState();
		Turndir = Cody->GetTurnDir();
		SinAngle = Cody->GetSin();
		Angle = Cody->GetAngle();
		CurrentJumpCount = Cody->GetJumpCount();
		IsDoubleJumped = Cody->GetDoubleJumped();
		Direction = Cody->GetRotateDirection();
		IsMovingOnGround = Cody->GetMovementComponent()->IsMovingOnGround();
	}
}
