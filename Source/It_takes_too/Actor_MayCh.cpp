// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_MayCh.h"

AActor_MayCh::AActor_MayCh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MAY(TEXT("SkeletalMesh'/Game/MayCharacter/May.May'"));
	if (SK_MAY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MAY.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> MAY_ANIM(TEXT("AnimBlueprint'/Game/MayCharacter/Blueprints/Actor_May_Anim_BP.Actor_May_Anim_BP_C'"));
	if (MAY_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(MAY_ANIM.Class);
	}

protected:
	bool hasHammer;
}