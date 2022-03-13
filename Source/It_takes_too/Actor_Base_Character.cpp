// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Base_Character.h"
#include "ABasePawn.h"

// Sets default values
AActor_Base_Character::AActor_Base_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CheckShift = false;
	CheckCtrl = false;
	CheckSpace = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CODY(TEXT("SkeletalMesh'/Game/BaseCharacter/untitled.untitled'"));
	if (SK_CODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CODY.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> CODY_IDLE_ANIM(TEXT("/Game/BaseCharacter/Blueprints/ActorAnim_BP.ActorAnim_BP_C"));
	if (CODY_IDLE_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CODY_IDLE_ANIM.Class);
	}

	SetControlMode(EJoomMode::NORMAL);

	Speedrate = 1.0f;
}

// Called when the game starts or when spawned
void AActor_Base_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_Base_Character::SetControlMode(EJoomMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case EJoomMode::NORMAL:
		SpringArm->TargetArmLength = 500.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
		break;

	case EJoomMode::NAILMODE:
		SpringArm->TargetArmLength = 130.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->SetRelativeLocation(FVector(0.0f, 50.0f, 100.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
}

// Called every frame
void AActor_Base_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckShift == true)	 Speedrate = 2.0f;
	else	Speedrate = 1.0f;

	if (CheckCtrl == true)	Speedrate = 0.4f;
	else	Speedrate = 1.0f;
}

// Called to bind functionality to input
void AActor_Base_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("JoomIn"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::JoomIn);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AActor_Base_Character::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::StartWalk);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Released, this, &AActor_Base_Character::StopWalk);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::Jump);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AActor_Base_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AActor_Base_Character::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AActor_Base_Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AActor_Base_Character::Turn);
}

void AActor_Base_Character::UpDown(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EJoomMode::NORMAL:
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), NewAxisValue * Speedrate);
		AtoCAngle = GetActorForwardVector().CosineAngle2D(FVector(1.0f, 0.0f, 0.0f));
		break;		// (1,0,0)

	case EJoomMode::NAILMODE:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), (NewAxisValue / 5) * Speedrate);
		break;
	}
}

void AActor_Base_Character::LeftRight(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EJoomMode::NORMAL:
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), NewAxisValue * Speedrate);
		AtoCAngle = GetActorForwardVector().CosineAngle2D(FVector(1.0f, 0.0f, 0.0f));
		ToGoDir = NewAxisValue;
		break;	//(0 , 1 , 0)

	case EJoomMode::NAILMODE:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), (NewAxisValue / 5) * Speedrate);
		ToGoDir = NewAxisValue;
		break;
	}
}

void AActor_Base_Character::LookUp(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EJoomMode::NORMAL:
		AddControllerYawInput(NewAxisValue);
		break;

	case EJoomMode::NAILMODE:
		AddControllerYawInput(NewAxisValue / 7);
		break;
	}
}

void AActor_Base_Character::Turn(float NewAxisValue)
{
	switch (CurrentControlMode)
	{
	case EJoomMode::NORMAL:
		AddControllerPitchInput(NewAxisValue);
		break;

	case EJoomMode::NAILMODE:
		AddControllerPitchInput(NewAxisValue / 7);
		break;
	}
}

void AActor_Base_Character::Jump()
{
	Super::Jump();
	JumpMaxCount = 2;
	CheckSpace = JumpCurrentCount;
	GetCharacterMovement()->JumpZVelocity = 800.0f;
}

void AActor_Base_Character::StartSprint()
{
	CheckShift = true;
	UE_LOG(LogTemp, Warning, L"StartSprint");
}

void AActor_Base_Character::StopSprint()
{
	CheckShift = false;
	UE_LOG(LogTemp, Warning, L"StopSprint");
}
void AActor_Base_Character::StartWalk()
{
	CheckCtrl = true;
}
void AActor_Base_Character::StopWalk()
{
	CheckCtrl = false;
}
float AActor_Base_Character::GetPressDirection()
{
	return ToGoDir;
}

bool AActor_Base_Character::GetPressShift()
{
	return CheckShift;
}

bool AActor_Base_Character::GetPressCtrl()
{
	return CheckCtrl;
}

int32 AActor_Base_Character::GetPressSpace()
{
	return CheckSpace;
}

float AActor_Base_Character::GetAngle()
{
	return AtoCAngle;
}

void AActor_Base_Character::JoomIn()
{
	switch (CurrentControlMode)
	{
	case EJoomMode::NORMAL:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EJoomMode::NAILMODE);
		break;
	case EJoomMode::NAILMODE:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EJoomMode::NORMAL);
	}
}

