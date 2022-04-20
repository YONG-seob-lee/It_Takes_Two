// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_MayCh.h"
<<<<<<< HEAD
=======
#include "../AnimInstance/May_AnimInst.h"

AActor_MayCh::AActor_MayCh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MAY(TEXT("SkeletalMesh'/Game/MayCharacter/May.May'"));
	if (SK_MAY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MAY.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_MAY(TEXT("AnimBlueprint'/Game/MayCharacter/Blueprints/Actor_May_Anim_BP.Actor_May_Anim_BP_C'"));
	if (ANIM_MAY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_MAY.Class);
	}

	FName HammerSocket(L"Backpack_end");
	if (GetMesh()->DoesSocketExist(HammerSocket))
	{
		Hammer = CreateDefaultSubobject<USkeletalMeshComponent>(L"WEAPON");
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Hammer(TEXT("SkeletalMesh'/Game/MayCharacter/Hammer.Hammer'"));
		if (SK_Hammer.Succeeded())
		{
			Hammer->SetSkeletalMesh(SK_Hammer.Object);
		}

		Hammer->SetupAttachment(GetMesh(), HammerSocket);
		Hammer->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(270.0f, 180.0f, 0.0f));
		Hammer->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	}
}

void AActor_MayCh::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Hammering"), EInputEvent::IE_Pressed, this, &AActor_MayCh::Hammering);
	PlayerInputComponent->BindAction(TEXT("NailSwing"), EInputEvent::IE_Pressed, this, &AActor_MayCh::NailSwing);
}

void AActor_MayCh::Hammering()
{
	if (!(CharState == ECharacterState::Idle)) return;

	UE_LOG(LogTemp, Warning, L"HammeringLog");
	CharState = ECharacterState::Hammering;
}

void AActor_MayCh::NailSwing()
{
	if (CharState == ECharacterState::Idle) return;

	if (CharState != ECharacterState::NailSwing)
	{
		UE_LOG(LogTemp, Warning, L"NailSwingLog");
		CharState = ECharacterState::NailSwing;
	}
	else
	{
		UE_LOG(LogTemp, Warning, L"NailSwingEndLog");
		CharState = ECharacterState::Idle;
	}	
}

void AActor_MayCh::HammeringEnd()
{
	UE_LOG(LogTemp, Warning, L"HammeringEndLog");
	CharState = ECharacterState::Idle;
}
>>>>>>> dabc9494911cf9650bee4da0bbbbb1e542191f82
