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
	InputComponent->BindAction("RightShoulder", IE_Pressed, this, &AfsCharacter::doRightShoulder);
    InputComponent->BindAction("RightTrigger", IE_Pressed, this, &AfsCharacter::doRightTrigger);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AfsCharacter::doJump);
    InputComponent->BindAction("Mode",IE_Pressed,this,&AfsCharacter::CharacterModeChange);
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

void AfsCharacter::doMeleeHvy()
{
    if(MeleeAllowed)
    {
        MeleeAllowed = false;
        PlayAnimMontage(astMeleeHvy);
        GetWorldTimerManager().SetTimer(MeleeTimer,this,&AfsCharacter::MeleeCold,HeavyDelay,false);
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
void AfsCharacter::CharacterModeChange()
{
    if(SwitchAllowed)
    {
        switch(CharacterMode)
        {
            case 0://melee
                CharacterMode = 1;
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode gun"));
                break;
            case 1://gun
                CharacterMode = 2;
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode magic"));
                break;
            case 2://magic or special
                CharacterMode = 0;
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode melee"));
                break;
        }
        SwitchAllowed = false;
        GetWorldTimerManager().SetTimer(SwitchTimer,this,&AfsCharacter::SwitchCold,SwitchDelay,false);
    }
}
void AfsCharacter::SwitchCold()
{
    SwitchAllowed = true;
}
void AfsCharacter::doRightShoulder()
{
    if(CharacterMode == 0)
        doMeleeLgt();
}
void AfsCharacter::doRightTrigger()
{
    if(CharacterMode == 0)
        doMeleeHvy();
}