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
	bIsAimed = false;
	Speedrate = 2.0f;			// 속도계수

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
	LandedDelegate.AddDynamic(this, &AActor_Base_Character::EndJump);
}

// Called every frame
void AActor_Base_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AActor_Base_Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AActor_Base_Character::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AActor_Base_Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AActor_Base_Character::Turn);
}

void AActor_Base_Character::UpDown(float NewAxisValue)
{
	switch (CurrentAimingMode)
	{
	case AimingMode::Normal:
	{
		Speedrate = 2.0f;
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, NewAxisValue * Speedrate);
		AtoCAngle = GetActorForwardVector().DegreesToRadians(FollowingCamera->GetForwardVector());
		break;
	}
	case AimingMode::Aiming:
	{
		Speedrate = 0.5;
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		break;
	}
	}
}

void AActor_Base_Character::LeftRight(float NewAxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, NewAxisValue * Speedrate);
	AtoCAngle = GetActorForwardVector().RadiansToDegrees(FollowingCamera->GetForwardVector());
	ToGoDir = NewAxisValue;
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
	if (bIsAimed)	return;
	Super::Jump();
	JumpMaxCount = 2;
	GetCharacterMovement()->bImpartBaseVelocityZ = 10;
	GetCharacterMovement()->JumpZVelocity = 800.0f;
}

void AActor_Base_Character::EndJump(const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("EndJump"));
}

void AActor_Base_Character::StartSprint()
{
	if (bIsAimed)	return;
	CheckShift = true;
	GetCharacterMovement()->MaxWalkSpeed *= Speedrate;
	OnSprint.Broadcast();
	UE_LOG(LogTemp, Warning, L"StartSprint");
}

void AActor_Base_Character::StopSprint()
{
	if (bIsAimed)	return;
	CheckShift = false;
	GetCharacterMovement()->MaxWalkSpeed /= Speedrate;

	UE_LOG(LogTemp, Warning, L"StopSprint");
}

void AActor_Base_Character::StartWalk()
{
	CheckCtrl = true;
	GetCharacterMovement()->MaxWalkSpeed /= Speedrate;
}

void AActor_Base_Character::StopWalk()
{
	CheckCtrl = false;
	GetCharacterMovement()->MaxWalkSpeed *= Speedrate;
}

void AActor_Base_Character::Aim()
{
	if (CheckShift)	return;

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
	if (CheckShift)	return;

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

bool AActor_Base_Character::GetPressShift()
{
	return CheckShift;
}

bool AActor_Base_Character::GetPressCtrl()
{
	return CheckCtrl;
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



