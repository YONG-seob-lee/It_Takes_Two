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

	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_MAY(TEXT("AnimBlueprint'/Game/MayCharacter/Blueprints/Actor_May_Anim_BP.Actor_May_Anim_BP_C'"));
	if (ANIM_MAY.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_MAY.Class);
	}

	FName HammerSocket(L"Spine2");
	if (GetMesh()->DoesSocketExist(HammerSocket))
	{
		Hammer = CreateDefaultSubobject<USkeletalMeshComponent>(L"WEAPON");
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Hammer(TEXT("SkeletalMesh'/Game/MayCharacter/Hammer.Hammer'"));
		if (SK_Hammer.Succeeded())
		{
			Hammer->SetSkeletalMesh(SK_Hammer.Object);
		}

		Hammer->SetupAttachment(GetMesh(), HammerSocket);
		Hammer->SetRelativeLocationAndRotation(FVector(-0.1f, 0.0f, 0.0f), FRotator(270.0f, 180.0f, 0.0f));
		Hammer->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	}
}

void AActor_MayCh::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Hammering"), EInputEvent::IE_Pressed, this, &AActor_MayCh::Hammering);
}

void AActor_MayCh::Hammering()
{
	UE_LOG(LogTemp, Warning, L"HammeringLog");
	CharState = ECharacterState::Hammering;
}