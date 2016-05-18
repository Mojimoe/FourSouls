// Fill out your copyright notice in the Description page of Project Settings.

#include "FourSouls.h"
#include "fsCharacter.h"


// Sets default values
AfsCharacter::AfsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PlayerCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCameraArm"));
    PlayerCameraArm->bUsePawnControlRotation = true;
    PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
    PlayerCameraArm->AttachParent = GetCapsuleComponent();
    PlayerCamera->AttachParent = PlayerCameraArm;
    MeleeAllowed=true;

}

// Called when the game starts or when spawned
void AfsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AfsCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AfsCharacter::MoveX(float in)
{
    if(in)
    {
        AddMovementInput(GetActorForwardVector(),in);
    }
}
void AfsCharacter::MoveY(float in)
{
    if(in)
    {
        AddMovementInput(GetActorRightVector(),in);
    }
}

// Called to bind functionality to input
void AfsCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("MeleeLgt", IE_Pressed, this, &AfsCharacter::doMeleeLgt);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AfsCharacter::doJump);
    InputComponent->BindAxis("Player_X",this,&AfsCharacter::MoveX);
    InputComponent->BindAxis("Player_Y",this,&AfsCharacter::MoveY);
    InputComponent->BindAxis("Player_Yaw",this,&AfsCharacter::AddControllerYawInput);
    InputComponent->BindAxis("Player_Pitch",this,&AfsCharacter::AddControllerPitchInput);
	InputComponent->BindAxis("Player_XGP", this, &AfsCharacter::MoveX);
	InputComponent->BindAxis("Player_YGP", this, &AfsCharacter::MoveY);
	InputComponent->BindAxis("Player_YawGP", this, &AfsCharacter::AddControllerYawInputGP);
	InputComponent->BindAxis("Player_PitchGP", this, &AfsCharacter::AddControllerPitchInputGP);
}

void AfsCharacter::AddControllerYawInputGP(float in)
{
	AddControllerYawInput(YawSensitivity*in);
}

void AfsCharacter::AddControllerPitchInputGP(float in)
{
	AddControllerPitchInput(PitchSensitivity*in);
}

float AfsCharacter::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
    USkeletalMeshComponent* UseMesh = GetMesh();
    if(AnimMontage&&UseMesh&&UseMesh->AnimScriptInstance)
    {
        return UseMesh->AnimScriptInstance->Montage_Play(AnimMontage,InPlayRate);
    }
    return 0.0f;
}

void AfsCharacter::MeleeCold()
{
    MeleeAllowed = true;
    //GetWorldTimerManager().ClearTimer(MeleeTimer); unnecessary because of false repeat flag.
}

void AfsCharacter::doMeleeLgt()
{
    if(MeleeAllowed)
    {
        MeleeAllowed = false;
        PlayAnimMontage(astMeleeLgt);
        GetWorldTimerManager().SetTimer(MeleeTimer,this,&AfsCharacter::MeleeCold,LightDelay,false);
    }
}

void AfsCharacter::doJump()
{
	UCharacterMovementComponent *charmov = this->GetCharacterMovement();
	if (charmov->MovementMode != MOVE_Walking)
	{
		JumpVal += 1;
	}
	if (JumpVal <= 2)
	{
		charmov->MovementMode = MOVE_Falling;
		charmov->Velocity.Z = JumpVelocity;
		//Jump();
	}
	JumpVal += 1;
}
void AfsCharacter::Landed(const FHitResult &Hit)
{
	Super::Landed(Hit);
	JumpVal = 0;
}