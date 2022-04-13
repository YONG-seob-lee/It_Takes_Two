// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Base_Character.h"
#include "ABasePawn.h"

#include "BaseCh_AnimInst.h"

// Sets default values
AActor_Base_Character::AActor_Base_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotateRate = 1.0f;			// 속도계수
	CurrentPawnSpeed = 0.0f;
	RotateDirection = 0.0f;
	beCrouched = false;
	IsHoldingWalk = false;
	IsHoldingSprint = false;
	IsDoubleJumped = false;
	TurnDir = ETurn::Center;		// Generally turn left. because Cody is Left-handed 
	CharState = ECharacterState::Idle;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 200.0f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
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

	// 자식 클래스에서 따로 입히는 중

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CODY(TEXT("SkeletalMesh'/Game/BaseCharacter/untitled.untitled'"));
	//if (SK_CODY.Succeeded())
	//{
	//	GetMesh()->SetSkeletalMesh(SK_CODY.Object);
	//}

	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	//static ConstructorHelpers::FClassFinder<UAnimInstance> CODY_IDLE_ANIM(TEXT("/Game/BaseCharacter/Blueprints/ActorAnim_BP.ActorAnim_BP_C"));
	//if (CODY_IDLE_ANIM.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(CODY_IDLE_ANIM.Class);
	//}
}

ECharacterState AActor_Base_Character::GetState()
{
	return CharState;
}

ETurn AActor_Base_Character::GetTurnDir()
{
	return TurnDir;
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
		CameraBoomAiming->bInheritPitch = true;				// Pitch 값을 상속받는다
		CameraBoomAiming->bInheritRoll = true;
		CameraBoomAiming->bInheritYaw = true;
		CameraBoomAiming->bUsePawnControlRotation = true;	// 폰의 회전이 카메라회전에 영향을 안미침
		CameraBoomAiming->bEnableCameraRotationLag = true;	// 카메라 회전을 smooth 하게 만들어줌
		bUseControllerRotationYaw = false;						// 컨트롤러의 회전으로 캐릭터가 회전 할 수 있냐/없냐
		GetCharacterMovement()->bOrientRotationToMovement = false;	// 자동적으로 캐릭터의 이동방향을 움직이는 방향에 맞춰준다.
		GetCharacterMovement()->bUseControllerDesiredRotation = true;	// 컨트롤러의 방향으로 부드럽게 회전
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		bUseControllerRotationPitch = false;				// 상속받은 Pitch 값에 따라 캐릭터가 따라서 회전하지 못하게 함.
		bUseControllerRotationYaw = true;
		bUseControllerRotationRoll = false;
		break;
	}
	}
}

void AActor_Base_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LandedDelegate.AddDynamic(this, &AActor_Base_Character::EndJump);
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

FString AActor_Base_Character::GetETurnAtString(ETurn EnumValue)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETurn"), true);
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

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetEStateAsString(CharState));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), GetCharacterMovement()->IsFalling() ? TEXT("True") : TEXT("False"));
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
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::DoCrouch);
	PlayerInputComponent->BindAction(TEXT("Roll"), EInputEvent::IE_Pressed, this, &AActor_Base_Character::Roll);
	
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AActor_Base_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AActor_Base_Character::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AActor_Base_Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AActor_Base_Character::Turn);
}

void AActor_Base_Character::UpDown(float NewAxisValue)
{
	// State Part    1. do not "Fully" use axis values	'wasd'를 아얘 사용 안하는 스테이트
	if (CharState == ECharacterState::Roll || CharState == ECharacterState::ThrowStart\
		|| CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire || CharState == ECharacterState::Hammering)	return;

	// 2. Special Case
	if (GetMovementComponent()->IsFalling() == true && CurrentAimingMode == AimingMode::Normal) {
		CharState = ECharacterState::Jump;
		if (JumpCurrentCount == 2)	IsDoubleJumped = true;
	}

	else if (GetMovementComponent()->IsFalling() == true && CurrentAimingMode == AimingMode::Aiming) {
		CharState = ECharacterState::JumpAiming;
		if (JumpCurrentCount == 2)	IsDoubleJumped = true;
	}

	else if (GetMovementComponent()->IsCrouching() == true)		CharState = ECharacterState::Crouch;

	else if (CurrentAimingMode == AimingMode::Aiming && IsHoldingWalk == true) {
		CharState = ECharacterState::WalkAiming;
		GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	}

	else if (CurrentAimingMode == AimingMode::Aiming && IsHoldingWalk == false) {
		CharState = ECharacterState::NormalAiming;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
	
	// 3. perfectly do not use axis value(default state)
	else if (GetMovementComponent()->GetLastInputVector() == FVector(0.0f, 0.0f, 0.0f) && GetMovementComponent()->Velocity.Size() == 0.0f)
	{
		CharState = ECharacterState::Idle;
		IsDoubleJumped = false;
	}
	// 4. use axis valus but are not in the "Jogging" state
	
	else
	{
		if (CharState == ECharacterState::Walk || IsHoldingWalk == true)
		{
			CharState = ECharacterState::Walk;
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;	
		}
		else if (CharState == ECharacterState::Sprint || IsHoldingSprint == true)
		{
			GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
		}
		else if (CharState == ECharacterState::NormalRecall)	CharState = ECharacterState::NormalRecall;
		else if (CharState == ECharacterState::WalkRecall)	CharState = ECharacterState::WalkRecall;
		else
		{
			CharState = ECharacterState::Jogging;
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}
	/////////////////

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, NewAxisValue);

		FVector CurrentContVector = GetPendingMovementInputVector();
		FVector ActorVector = GetActorForwardVector();
		FVector2D CurrentConVector2D = { CurrentContVector.X, CurrentContVector.Y };
		FVector2D ActorVector2D = { ActorVector.X, ActorVector.Y };
		CurrentConVector2D.Normalize();
		dot = FVector2D::DotProduct(CurrentConVector2D, ActorVector2D);		// 내적을 구함
		cross = FVector2D::CrossProduct(CurrentConVector2D, ActorVector2D);	// 외적을 구함
		Angle = FMath::RadiansToDegrees(FMath::Acos(dot));
		SinAngle = FMath::Sin(Angle);
		if (cross > 0.3f) TurnDir = ETurn::Right;					// 30도로 돌아가면 고개가 돌아감
		else if (cross < -0.3f)	TurnDir = ETurn::Left;				// -30도로 돌아가면 고개가 돌아감
		else	TurnDir = ETurn::Center;
}

void AActor_Base_Character::LeftRight(float NewAxisValue)
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	RotateRate = 1.0f;
	// State Part    1. do not "Fully" use axis values	'wasd'를 아얘 사용 안하는 스테이트
	if (CharState == ECharacterState::Roll || CharState == ECharacterState::ThrowStart\
		|| CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire || CharState == ECharacterState::Hammering)	return;

	// 2. Special Case
	if (GetMovementComponent()->IsFalling() == true && CurrentAimingMode == AimingMode::Normal){
		CharState = ECharacterState::Jump;
		if (JumpCurrentCount == 2)	IsDoubleJumped = true;
	}

	else if (GetMovementComponent()->IsFalling() == true && CurrentAimingMode == AimingMode::Aiming){
		CharState = ECharacterState::JumpAiming;
		if (JumpCurrentCount == 2)	IsDoubleJumped = true;
	}

	else if (GetMovementComponent()->IsCrouching() == true) CharState = ECharacterState::Crouch;

	else if (CurrentAimingMode == AimingMode::Aiming && IsHoldingWalk == true) {
		CharState = ECharacterState::WalkAiming;
		GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	}

	else if (CurrentAimingMode == AimingMode::Aiming && IsHoldingWalk == false) {
		CharState = ECharacterState::NormalAiming;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}

	// 3. perfectly do not use axis value(default state)
	else if (GetMovementComponent()->GetLastInputVector() == FVector(0.0f, 0.0f, 0.0f) && GetMovementComponent()->Velocity.Size() == 0.0f)
	{
		CharState = ECharacterState::Idle;
		IsDoubleJumped = false;
	}
	// 4. use axis valus but are not in the "Jogging" state
	else
	{
		if (CharState == ECharacterState::Walk || IsHoldingWalk == true)
		{
			CharState = ECharacterState::Walk;
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		}
		else if (CharState == ECharacterState::Sprint || IsHoldingSprint == true)
		{
			GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
			GetCharacterMovement()->bOrientRotationToMovement = false;
			RotateRate = 0.35f;
		}
		else if (CharState == ECharacterState::NormalRecall)	CharState = ECharacterState::NormalRecall;
		else if (CharState == ECharacterState::WalkRecall)	CharState = ECharacterState::WalkRecall;
		else
		{
			CharState = ECharacterState::Jogging;
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		}
	}
	/////////////////
	RotateDirection = NewAxisValue * 180.0f;
	ToGoDir = NewAxisValue;

	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, NewAxisValue * RotateRate);
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
	if (CharState == ECharacterState::StopJump || CharState == ECharacterState::Roll || CharState == ECharacterState::Crouch \
		|| CharState == ECharacterState::NormalAiming || CharState == ECharacterState::WalkAiming\
		|| CharState == ECharacterState::ThrowStart || CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire\
 		|| CharState == ECharacterState::NormalRecall || CharState == ECharacterState::WalkRecall || CharState == ECharacterState::Hammering)	return;
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
	UE_LOG(LogTemp, Warning, TEXT("StopJump"));
}

void AActor_Base_Character::EndJump(const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("EndJump"));
	if (IsHoldingSprint == true)	CharState = ECharacterState::Sprint;
}

void AActor_Base_Character::DoCrouch()
{
	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::Sprint || CharState == ECharacterState::Jump || CharState == ECharacterState::JumpAiming\
		|| CharState == ECharacterState::StopJump || CharState == ECharacterState::Roll\
		|| CharState == ECharacterState::NormalAiming || CharState == ECharacterState::WalkAiming || CharState == ECharacterState::Acquire\
		|| CharState == ECharacterState::NormalRecall || CharState == ECharacterState::WalkRecall || CharState == ECharacterState::ThrowStart\
		|| CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Hammering)	return;

	if (GetCharacterMovement()->bWantsToCrouch == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("DoCrouch"));
		Crouch();
		CharState = ECharacterState::Crouch;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UnCrouch"));
		UnCrouch();
		CharState = ECharacterState::Idle;
	}
}

void AActor_Base_Character::Roll()
{
	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::Roll || CharState == ECharacterState::Crouch || CharState == ECharacterState::Hammering)	return;

	CharState = ECharacterState::Roll;
	GetCharacterMovement()->JumpZVelocity = 10.0f;
	GetCharacterMovement()->AddForce(GetActorForwardVector() * 2000);
	UE_LOG(LogTemp, Warning, TEXT("Roll"));
	if (GetMesh()->GetAnimInstance() == nullptr) {
		UE_LOG(LogTemp, Warning, L"NULL");
	}

	Cast<UBaseCh_AnimInst>(GetMesh()->GetAnimInstance())->RollAnimMontage();
}

void AActor_Base_Character::StartSprint()
{
	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::Idle || CharState == ECharacterState::StopJump || CharState == ECharacterState::Jump\
		|| CharState == ECharacterState::JumpAiming || CharState == ECharacterState::Roll || CharState == ECharacterState::Crouch\
		|| CharState == ECharacterState::ThrowStart || CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire || CharState == ECharacterState::Hammering)	return;

	// 2. especially acceptable
	else if (CharState == ECharacterState::NormalAiming || CharState == ECharacterState::WalkAiming || CharState == ECharacterState::NormalRecall\
		|| CharState == ECharacterState::WalkRecall) {
		CharState = ECharacterState::Sprint;
		IsHoldingSprint = true;
	}

	// 3. own state of using the axis values(Walk, Jogging)
	else
	{
		CharState = ECharacterState::Sprint;
		IsHoldingSprint = true;
	}
	//////////////
	UE_LOG(LogTemp, Warning, L"StartSprint");
}

void AActor_Base_Character::StopSprint()
{
	if (CharState == ECharacterState::Crouch)	return;
	CharState = ECharacterState::Idle;
	IsHoldingSprint = false;
	UE_LOG(LogTemp, Warning, L"StopSprint");
}

void AActor_Base_Character::StartWalk()
{
	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::Idle || CharState == ECharacterState::Jump ||CharState == ECharacterState::StopJump\
		|| CharState == ECharacterState::JumpAiming || CharState == ECharacterState::Crouch || CharState == ECharacterState::ThrowStart\
		|| CharState == ECharacterState::ThrowEnd || CharState == ECharacterState::Acquire || CharState == ECharacterState::Hammering)	return;

	else if (CharState == ECharacterState::NormalAiming || CharState == ECharacterState::WalkAiming)
	{
		IsHoldingWalk = true;
		CharState = ECharacterState::WalkAiming;
	}

	// 2. especially acceptable
	else if (CharState == ECharacterState::NormalAiming || CharState == ECharacterState::WalkAiming\
		|| CharState == ECharacterState::NormalRecall || CharState == ECharacterState::WalkRecall)
	{
		IsHoldingWalk = true;
		CharState = ECharacterState::Walk;
	}

	// 3. own state of using the axis values(Walk, Jogging)
	else {
		IsHoldingWalk = true;
		CharState = ECharacterState::Walk;
	}
	//////////////
}

void AActor_Base_Character::StopWalk()
{
	CharState = ECharacterState::Idle;
	IsHoldingWalk = false;
}

void AActor_Base_Character::Aim()
{
	SetAimingMode(AimingMode::Aiming);

	// State Part    1. can't be overlapped(action)
	if (CharState == ECharacterState::Sprint || CharState == ECharacterState::Roll || CharState == ECharacterState::Crouch\
		|| CharState == ECharacterState::StopJump || CharState == ECharacterState::ThrowStart || CharState == ECharacterState::ThrowEnd\
		|| CharState == ECharacterState::Acquire || CharState == ECharacterState::Hammering)	return;
	
	else
	{
		if (IsHoldingWalk == true)	CharState = ECharacterState::WalkAiming;
		else	CharState = ECharacterState::NormalAiming;
	}
	//////////////
	UE_LOG(LogTemp, Warning, TEXT("Aim"));

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	FollowingCamera->AttachToComponent(CameraBoomAiming, FAttachmentTransformRules::KeepWorldTransform);
	UKismetSystemLibrary::MoveComponentTo(FollowingCamera, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), true, true, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);
	GetController()->SetControlRotation(CameraBoomAiming->GetRelativeRotation());
}

void AActor_Base_Character::StopAim()
{
	SetAimingMode(AimingMode::Normal);
	UE_LOG(LogTemp, Warning, TEXT("AimStop"));
	CharState = ECharacterState::Idle;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	FollowingCamera->AttachToComponent(CameraBoomNormal, FAttachmentTransformRules::KeepWorldTransform);
	UKismetSystemLibrary::MoveComponentTo(FollowingCamera, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), true, true, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);
}

float AActor_Base_Character::GetPressDirection()
{
	return ToGoDir;
}

int32 AActor_Base_Character::GetJumpCount()
{
	return JumpCurrentCount;
}

float AActor_Base_Character::GetAngle()
{
	return Angle;
}

float AActor_Base_Character::GetSin()
{
	return SinAngle;
}

float AActor_Base_Character::GetRotateDirection()
{
	return RotateDirection;
}

bool AActor_Base_Character::GetDoubleJumped()
{
	return IsDoubleJumped;
}

void AActor_Base_Character::SetEndRoll()
{
	CharState = ECharacterState::Idle;
}



