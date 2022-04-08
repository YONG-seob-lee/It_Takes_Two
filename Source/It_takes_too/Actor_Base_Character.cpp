// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Base_Character.h"
#include "ABasePawn.h"

// Sets default values
AActor_Base_Character::AActor_Base_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsAimed = false;
	Speedrate = 2.0f;			// 속도계수
	CurrentPawnSpeed = 0.0f;
	CharState = ECharacterState::Idle;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	FollowingCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CameraBoomNormal = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERABOOOMNORMAL"));
	CameraBoomAiming = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERABOOMAIMING"));

	CameraBoomNormal->SetupAttachment(RootComponent);
	CameraBoomAiming->SetupAttachment(GetCapsuleComponent());
	FollowingCamera->SetupAttachment(CameraBoomNormal);

	CameraBoomNormal->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-25.0f, 0.0f, 0.0f));
	CameraBoomAiming->SetRelativeLocationAndRotation(FVector(50.0f, 50.0f, 50.0f), FRotator(-15.0f, 0.0f, 0.0f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	SetAimingMode(AimingMode::Normal);

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
}

ECharacterState AActor_Base_Character::GetState()
{
	return CharState;
}

// Called when the game starts or when spawned
void AActor_Base_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_Base_Character::SetAimingMode(AimingMode NewAimingMode)
{
	CurrentAimingMode = NewAimingMode;

	switch (CurrentAimingMode)
	{
	case AimingMode::Normal:
	{
		CameraBoomNormal->TargetArmLength = 500.0f;
		CameraBoomNormal->bEnableCameraLag = true;
		CameraBoomNormal->bEnableCameraRotationLag = true;
		CameraBoomNormal->CameraLagSpeed = 3.0f;
		CameraBoomNormal->bUsePawnControlRotation = true;		// 컨트롤러의 회전을 마우스가 능동적으로 바뀜
		CameraBoomNormal->bInheritPitch = true;					// SpringArm 상속받아온다
		CameraBoomNormal->bInheritRoll = true;					// SpringArm 상속받아온다
		CameraBoomNormal->bInheritYaw = true;					// SpringArm 상속받아온다
		CameraBoomNormal->bDoCollisionTest = true;				// 카메라가 벽을 뚫고 갈지 말지
		bUseControllerRotationYaw = false;						// 컨트롤러의 회전으로 캐릭터가 회전 할 수 있냐/없냐
		GetCharacterMovement()->bOrientRotationToMovement = true;	// 자동적으로 캐릭터의 이동방향을 움직이는 방향에 맞춰준다.
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}

	case AimingMode::Aiming:
	{
		CameraBoomAiming->TargetArmLength = 300.0f;
		CameraBoomAiming->SetRelativeRotation(FRotator::ZeroRotator);
		CameraBoomAiming->bDoCollisionTest = true;
		CameraBoomAiming->bInheritPitch = true;
		CameraBoomAiming->bInheritRoll = true;
		CameraBoomAiming->bInheritYaw = true;
		CameraBoomAiming->bUsePawnControlRotation = true;	// 폰의 회전이 카메라회전에 영향을 안미침
		bUseControllerRotationYaw = false;						// 컨트롤러의 회전으로 캐릭터가 회전 할 수 있냐/없냐
		GetCharacterMovement()->bOrientRotationToMovement = false;	// 자동적으로 캐릭터의 이동방향을 움직이는 방향에 맞춰준다.
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
	}
}

void AActor_Base_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

FString AActor_Base_Character::GetEStateAsString(ECharacterState EnumValue)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECharacterState"), true);
	if (!enumPtr)
	{
		return FString("Invalid");
	}
	return enumPtr->GetNameStringByIndex((int32)EnumValue);
}

// Called every frame
void AActor_Base_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UKismetSystemLibrary::PrintString(GetWorld(), GetEStateAsString(CharState), true, false, FLinearColor::Green, 2.0f);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetEStateAsString(CharState));
}

// Called to bind functionality to input
void AActor_Base_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::Aim);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AActor_Base_Character::StopAim);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AActor_Base_Character::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::StartWalk);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Released, this, &AActor_Base_Character::StopWalk);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AActor_Base_Character::StopJumping);
	
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AActor_Base_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AActor_Base_Character::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AActor_Base_Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AActor_Base_Character::Turn);
}

void AActor_Base_Character::UpDown(float NewAxisValue)
{
	// State Part    1. do not "Fully" use axis values	'wasd'를 아얘 사용 안하는 스테이트
	if (CharState == ECharacterState::StopJump || CharState == ECharacterState::Roll || CharState == ECharacterState::ThrowStart\
		|| CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire)	return;

	if (GetMovementComponent()->IsFalling() == true)	CharState = ECharacterState::Jump;

	// 2. perfectly do not use axis value(default state)
	else if (GetMovementComponent()->GetLastInputVector() == FVector(0.0f, 0.0f, 0.0f))
	{
		CharState = ECharacterState::Idle;
	}
	// 3. use axis valus but are not in the "Jogging" state
	
	else
	{
		if (CharState == ECharacterState::Walk)
		{
			CharState = ECharacterState::Walk;
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		}
		else if (CharState == ECharacterState::Sprint)
		{
			CharState = ECharacterState::Sprint;
			GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
		}
		else if (CharState == ECharacterState::NormalAiming)	CharState = ECharacterState::NormalAiming;
		else if (CharState == ECharacterState::WalkAiming)	CharState = ECharacterState::WalkAiming;
		else if (CharState == ECharacterState::NormalRecall)	CharState = ECharacterState::NormalRecall;
		else if (CharState == ECharacterState::WalkRecall)	CharState = ECharacterState::WalkRecall;
		else
		{
			CharState = ECharacterState::Jogging;
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}
	/////////////////

	Speedrate = 2.0f;

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, NewAxisValue * Speedrate);

		FVector CurrentContVector = GetPendingMovementInputVector();
		FVector ActorVector = GetActorForwardVector();
		FVector2D CurrentConVector2D = { CurrentContVector.X, CurrentContVector.Y };
		FVector2D ActorVector2D = { ActorVector.X, ActorVector.Y };
		CurrentConVector2D.Normalize();
		dot = FVector2D::DotProduct(CurrentConVector2D, ActorVector2D);		// 내적을 구함
		Angle = FMath::RadiansToDegrees(FMath::Acos(dot));
		
	//	UE_LOG(LogTemp, Warning, TEXT("bePressed : %f, Angle : %f, CurrentV : %s, ActorV : %s"),NewAxisValue, Angle, *CurrentConVector2D.ToString(), *ActorVector2D.ToString());
	
}

void AActor_Base_Character::LeftRight(float NewAxisValue)
{
	GetMovementComponent()->AddInputVector(FVector(NewAxisValue, 0.0f, 0.0f));
	// State Part    1. do not "Fully" use axis values
	if (CharState == ECharacterState::StopJump || CharState == ECharacterState::Roll || CharState == ECharacterState::ThrowStart\
		|| CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire)	return;

	Speedrate = 2.0f;

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, NewAxisValue * Speedrate);
}

void AActor_Base_Character::LookUp(float NewAxisValue)
{
	switch (CurrentAimingMode)
	{
	case AimingMode::Normal:
	{
		AddControllerYawInput(NewAxisValue);
		break;
	}
	case AimingMode::Aiming:
	{
		AddControllerYawInput(NewAxisValue);
		break;
	}
	}
}

void AActor_Base_Character::Turn(float NewAxisValue)
{
	switch (CurrentAimingMode)
	{
	case AimingMode::Normal:
	{
		AddControllerPitchInput(NewAxisValue);
		break;
	}
	case AimingMode::Aiming:
	{
		AddControllerPitchInput(NewAxisValue);
		break;
	}
	}
}

void AActor_Base_Character::Jump()
{
	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::StopJump || CharState == ECharacterState::Roll\
		|| CharState == ECharacterState::Roll || CharState == ECharacterState::NormalAiming || CharState == ECharacterState::WalkAiming\
		|| CharState == ECharacterState::ThrowStart || CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire\
 		|| CharState == ECharacterState::NormalRecall || CharState == ECharacterState::WalkRecall || CharState == ECharacterState::StopSprint)	return;
	// 2. own state of using the axis values(jump is a unique case, so it is classified into four types)
	else CharState = ECharacterState::Jump;

	Super::Jump();
	UE_LOG(LogTemp, Warning, TEXT("Jump"));
	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.1f;
	GetCharacterMovement()->bImpartBaseVelocityZ = 10;
	GetCharacterMovement()->JumpZVelocity = 800.0f;
	GetCharacterMovement()->AirControl = 0.20f;
}

void AActor_Base_Character::StopJumping()
{
	Super::StopJumping();
	CharState = ECharacterState::Idle;
	UE_LOG(LogTemp, Warning, TEXT("EndJump"));
}

void AActor_Base_Character::StartSprint()
{
	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::Idle || CharState == ECharacterState::StopJump || CharState == ECharacterState::Jump || CharState == ECharacterState::Roll\
		|| CharState == ECharacterState::ThrowStart || CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire)	return;

	// 2. especially acceptable
	else if (CharState == ECharacterState::NormalAiming || CharState == ECharacterState::WalkAiming || CharState == ECharacterState::NormalRecall\
		|| CharState == ECharacterState::WalkRecall)	CharState = ECharacterState::Sprint;

	// 3. own state of using the axis values(Walk, Jogging)
	else	CharState = ECharacterState::Sprint;
	//////////////
	UE_LOG(LogTemp, Warning, L"StartSprint");
}

void AActor_Base_Character::StopSprint()
{
	CharState = ECharacterState::StopSprint;

	UE_LOG(LogTemp, Warning, L"StopSprint");
}

void AActor_Base_Character::StartWalk()
{
	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::Idle || CharState == ECharacterState::Jump ||CharState == ECharacterState::StopJump\
		|| CharState == ECharacterState::Roll || CharState == ECharacterState::ThrowStart || CharState == ECharacterState::ThrowEnd\
		|| CharState == ECharacterState::Acquire)	return;

	// 2. especially acceptable
	else if (CharState == ECharacterState::NormalAiming || CharState == ECharacterState::WalkAiming || CharState == ECharacterState::NormalRecall\
		|| CharState == ECharacterState::WalkRecall)	CharState = ECharacterState::Walk;

	// 3. own state of using the axis values(Walk, Jogging)
	else	CharState = ECharacterState::Walk;
	//////////////
}

void AActor_Base_Character::StopWalk()
{
	CharState = ECharacterState::Idle;
}

void AActor_Base_Character::Aim()
{

	// State part
	if (CharState == ECharacterState::Walk)	CharState = ECharacterState::WalkAiming;
	if (CharState == ECharacterState::Idle || CharState == ECharacterState::Jogging || CharState == ECharacterState::Sprint\
		|| CharState == ECharacterState::NormalRecall || CharState == ECharacterState::WalkRecall)
	{
		CharState = ECharacterState::NormalAiming;
	}
	//////////////
	UE_LOG(LogTemp, Warning, TEXT("Aim"));

	SetAimingMode(AimingMode::Aiming);
	bIsAimed = true;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	FollowingCamera->AttachToComponent(CameraBoomAiming, FAttachmentTransformRules::KeepWorldTransform);
	UKismetSystemLibrary::MoveComponentTo(FollowingCamera, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), true, true, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);
	GetController()->SetControlRotation(CameraBoomAiming->GetRelativeRotation());
}

void AActor_Base_Character::StopAim()
{
	UE_LOG(LogTemp, Warning, TEXT("AimStop"));

	bIsAimed = false;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	FollowingCamera->AttachToComponent(CameraBoomNormal, FAttachmentTransformRules::KeepWorldTransform);
	UKismetSystemLibrary::MoveComponentTo(FollowingCamera, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), true, true, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);
	SetAimingMode(AimingMode::Normal);
}

float AActor_Base_Character::GetPressDirection()
{
	return ToGoDir;
}

bool AActor_Base_Character::GetbIsAimed()
{
	return bIsAimed;
}

int32 AActor_Base_Character::GetJumpCount()
{
	return JumpCurrentCount;
}

float AActor_Base_Character::GetAngle()
{
	return 0.0f;
}



