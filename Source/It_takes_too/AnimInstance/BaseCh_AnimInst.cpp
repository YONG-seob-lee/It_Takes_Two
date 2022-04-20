// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCh_AnimInst.h"
#include "../Character/Actor_Base_Character.h"
#include "../Character/Actor_CodyCh.h"
<<<<<<< HEAD
=======
#include "../Character/Actor_MayCh.h"
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82

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

<<<<<<< HEAD

=======
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
void UBaseCh_AnimInst::AnimNotify_RollEndCheck()
{

	UE_LOG(LogTemp, Warning, L"AnimNotify_RollEndCheck");
<<<<<<< HEAD
	AActor_Base_Character* Cody = Cast<AActor_Base_Character>(GetOwningActor());
=======
	AActor_CodyCh* Cody = Cast<AActor_CodyCh>(GetOwningActor());
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
	
	Cody->SetEndRoll();
}

void UBaseCh_AnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


<<<<<<< HEAD
	AActor_Base_Character* Cody = Cast<AActor_Base_Character>(GetOwningActor());
=======
	AActor_CodyCh* Cody = Cast<AActor_CodyCh>(GetOwningActor());
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82

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
<<<<<<< HEAD
=======

	AActor_MayCh* May = Cast<AActor_MayCh>(GetOwningActor());
	if (IsValid(May))
	{
		CurrentPawnSpeed = May->GetVelocity().Size();
		JogDirection = May->GetPressDirection();

		if (JogDirection != 0.0f)
		{
			JogDirection = May->GetPressDirection();	// ?¢Ò¡¾? ?¢ç??
		}
		State = May->GetState();
		Turndir = May->GetTurnDir();
		SinAngle = May->GetSin();
		Angle = May->GetAngle();
		CurrentJumpCount = May->GetJumpCount();
		IsDoubleJumped = May->GetDoubleJumped();
		Direction = May->GetRotateDirection();
		IsMovingOnGround = May->GetMovementComponent()->IsMovingOnGround();
	}
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
}
