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
	CheckSpace = 0;
	bIsAimed = false;

	CameraBoomNormal = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERABOOOMNORMAL"));
	CameraBoomNormal->SetupAttachment(RootComponent);
	CameraBoomNormal->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-25.0f, 0.0f, 0.0f));
	CameraBoomNormal->TargetArmLength = 500.0f;
	CameraBoomNormal->bEnableCameraLag = true;
	CameraBoomNormal->bEnableCameraRotationLag = true;
	CameraBoomNormal->CameraLagSpeed = 3.0f;
	CameraBoomNormal->bUsePawnControlRotation = true;		// 컨트롤러의 회전을 마우스가 능동적으로 바뀜
	CameraBoomNormal->bInheritPitch = true;					// SpringArm 상속받아온다
	CameraBoomNormal->bInheritRoll = true;					// SpringArm 상속받아온다
	CameraBoomNormal->bInheritYaw = true;					// SpringArm 상속받아온다
	CameraBoomNormal->bDoCollisionTest = true;				// 카메라가 충돌해서 잘려보이지 않게 한다.
	bUseControllerRotationYaw = false;						// 컨트롤러의 회전을 부드럽게 하기 위한 변수
	GetCharacterMovement()->bOrientRotationToMovement = true;	// 자동적으로 캐릭터의 이동방향을 움직이는 방향에 맞춰준다.
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);


	CameraBoomAiming = CreateDefaultSubobject<USpringArmComponent>(TEXT("CAMERABOOMAIMING"));
	CameraBoomAiming->SetupAttachment(RootComponent);
	CameraBoomAiming->SetRelativeLocationAndRotation(FVector(200.0f, 50.0f, 50.0f), FRotator(-15.0f, 0.0f, 0.0f));
	CameraBoomAiming->TargetArmLength = 300.0f;
	CameraBoomAiming->bEnableCameraLag = true;
	CameraBoomAiming->CameraLagSpeed = 10.0f;

	FollowingCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	FollowingCamera->SetupAttachment(CameraBoomNormal);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

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

	//SetControlMode();

	Speedrate = 2.0f;
}

// Called when the game starts or when spawned
void AActor_Base_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_Base_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	LandedDelegate.AddDynamic(this, &AActor_Base_Character::EndJump);
}

void AActor_Base_Character::SetControlMode()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);
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
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, NewAxisValue * Speedrate);
	AtoCAngle = GetActorForwardVector().DegreesToRadians(FollowingCamera->GetForwardVector());
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
	AddControllerYawInput(NewAxisValue);
}

void AActor_Base_Character::Turn(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void AActor_Base_Character::Jump()
{
	if (bIsAimed)	return;
	Super::Jump();
	JumpMaxCount = 2;
	CheckSpace = JumpCurrentCount;
	GetCharacterMovement()->bApplyGravityWhileJumping = 10;
	GetCharacterMovement()->JumpZVelocity = 800.0f;
}

void AActor_Base_Character::EndJump(const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("EndJump"));
	CheckSpace = 0;
}

void AActor_Base_Character::StartSprint()
{
	if (bIsAimed)	return;
	CheckShift = true;
	GetCharacterMovement()->MaxWalkSpeed *= Speedrate;

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

	bIsAimed = true;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	FollowingCamera->AttachToComponent(CameraBoomAiming, FAttachmentTransformRules::KeepWorldTransform);
	UKismetSystemLibrary::MoveComponentTo(FollowingCamera, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), true, true, 0.2, false, EMoveComponentAction::Type::Move, LatentInfo);
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
	return 0.0f;
}



