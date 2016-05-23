// Fill out your copyright notice in the Description page of Project Settings.

#include "FourSouls.h"
#include "fsCharacter.h"
#include "fsWeapon.h"


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
}

// Called when the game starts or when spawned
void AfsCharacter::BeginPlay()
{
	Super::BeginPlay();
    FVector MeleeSpl = FVector::ZeroVector;
    FRotator MeleeSpr = FRotator::ZeroRotator;
    FActorSpawnParameters MeleeSpp;
    MeleeSpp.Instigator = this;
	MeleeWeapon = GetWorld()->SpawnActor<AfsWeapon>(MeleeWeaponToSpawn,MeleeSpl,MeleeSpr,MeleeSpp);
	if (MeleeWeapon)
	{
		MeleeWeapon->OnEquip(this);
		MeleeWeapon->IsMelee = true;
	}
    FVector RangedSpl = FVector::ZeroVector;
    FRotator RangedSpr = FRotator::ZeroRotator;
    FActorSpawnParameters RangedSpp;
    RangedSpp.Instigator = this;
	RangedWeapon = GetWorld()->SpawnActor<AfsWeapon>(RangedWeaponToSpawn,RangedSpl,RangedSpr,RangedSpp);
	if (RangedWeapon)
	{
		RangedWeapon->OnEquip(this);
		RangedWeapon->IsMelee = false;
	}
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
        InputComponent->BindAction("RightShoulder",IE_Pressed, this, &AfsCharacter::doRightShoulderPressed);
        InputComponent->BindAction("RightShoulder",IE_Released,this, &AfsCharacter::doRightShoulderReleased);
        InputComponent->BindAction("RightTrigger", IE_Pressed, this, &AfsCharacter::doRightTriggerPressed);
        InputComponent->BindAction("RightTrigger", IE_Released,this, &AfsCharacter::doRightTriggerReleased);
        InputComponent->BindAction("LeftShoulder", IE_Pressed, this, &AfsCharacter::doLeftShoulderPressed);
        InputComponent->BindAction("LeftShoulder", IE_Released,this, &AfsCharacter::doLeftShoulderReleased);
        InputComponent->BindAction("LeftTrigger",  IE_Pressed, this, &AfsCharacter::doLeftTriggerPressed);
        InputComponent->BindAction("LeftTrigger",  IE_Released,this, &AfsCharacter::doLeftTriggerReleased);
        InputComponent->BindAction("FaceBottom",   IE_Pressed, this, &AfsCharacter::doFaceBottomPressed);
        InputComponent->BindAction("FaceBottom",   IE_Released,this, &AfsCharacter::doFaceBottomReleased);
        InputComponent->BindAction("FaceTop",      IE_Pressed, this, &AfsCharacter::doFaceTopPressed);
        InputComponent->BindAction("FaceTop",      IE_Released,this, &AfsCharacter::doFaceTopReleased);
        InputComponent->BindAction("FaceRight",    IE_Pressed, this, &AfsCharacter::doFaceRightPressed);
        InputComponent->BindAction("FaceRight",    IE_Released,this, &AfsCharacter::doFaceRightReleased);
        InputComponent->BindAction("FaceLeft",     IE_Pressed, this, &AfsCharacter::doFaceLeftPressed);
        InputComponent->BindAction("FaceLeft",     IE_Released,this, &AfsCharacter::doFaceLeftReleased);
        InputComponent->BindAction("DpadUp",       IE_Pressed, this, &AfsCharacter::doDpadUpPressed);
        InputComponent->BindAction("DpadUp",       IE_Released,this, &AfsCharacter::doDpadUpReleased);
        InputComponent->BindAction("DpadRight",    IE_Pressed, this, &AfsCharacter::doDpadRightPressed);
        InputComponent->BindAction("DpadRight",    IE_Released,this, &AfsCharacter::doDpadRightReleased);
        InputComponent->BindAction("DpadDown",     IE_Pressed, this, &AfsCharacter::doDpadDownPressed);
        InputComponent->BindAction("DpadDown",     IE_Released,this, &AfsCharacter::doDpadDownReleased);
        InputComponent->BindAction("DpadLeft",     IE_Pressed, this, &AfsCharacter::doDpadLeftPressed);
        InputComponent->BindAction("DpadLeft",     IE_Released,this, &AfsCharacter::doDpadLeftReleased);
        InputComponent->BindAction("RightStick",   IE_Pressed, this, &AfsCharacter::doRightStickPressed);
        InputComponent->BindAction("RightStick",   IE_Released,this, &AfsCharacter::doRightStickReleased);
        InputComponent->BindAction("LeftStick",    IE_Pressed, this, &AfsCharacter::doLeftStickPressed);
        InputComponent->BindAction("LeftStick",    IE_Released,this, &AfsCharacter::doLeftStickReleased);
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


void AfsCharacter::doMeleeLgt()
{
    PlayAnimMontage(astMeleeLgt);
}

void AfsCharacter::doMeleeHvy()
{
    PlayAnimMontage(astMeleeHvy);
    //if(MeleeAllowed)
    //{
    //    MeleeAllowed = false;
    //    GetWorldTimerManager().SetTimer(MeleeTimer,this,&AfsCharacter::MeleeCold,HeavyDelay,false);
    //}
}
//INPUT HANDLERS---------------------------------------------------------------
void AfsCharacter::doRightShoulderPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Right Shoulder Pressed"));
	switch(CharacterMode)
    {
        case 0://melee
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Melee"));
			if(MeleeWeapon)MeleeWeapon->OnRightShoulderPressed();
            break;
        case 1://gun
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Ranged"));
			if(RangedWeapon)RangedWeapon->OnRightShoulderPressed();
            break;
        case 2://magic or special
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Magic"));
            break;
    }
}
void AfsCharacter::doRightShoulderReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Right Shoulder Released"));
	switch(CharacterMode)
    {
        case 0://melee
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Melee"));
			if(MeleeWeapon) MeleeWeapon->OnRightShoulderReleased();
            break;
        case 1://gun
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Ranged"));
			if(RangedWeapon)RangedWeapon->OnRightShoulderReleased();
            break;
        case 2://magic or special
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Magic"));
            break;
    }
}
void AfsCharacter::doRightTriggerPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Right Trigger Pressed"));
	switch(CharacterMode)
    {
        case 0://melee
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Melee"));
			if(MeleeWeapon)MeleeWeapon->OnRightTriggerPressed();
            break;
        case 1://gun
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Ranged"));
			if(RangedWeapon)RangedWeapon->OnRightTriggerPressed();
            break;
        case 2://magic or special
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Magic"));
            break;
    }
}
void AfsCharacter::doRightTriggerReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Right Trigger Released"));
	switch(CharacterMode)
    {
        case 0://melee
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Melee"));
			if(MeleeWeapon)MeleeWeapon->OnRightTriggerReleased();
            break;
        case 1://gun
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Ranged"));
			if(RangedWeapon)RangedWeapon->OnRightTriggerReleased();
            break;
        case 2://magic or special
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Magic"));
            break;
    }
}
void AfsCharacter::doLeftShoulderPressed()
{
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Left Shoulder Pressed"));
}
void AfsCharacter::doLeftShoulderReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Left Shoulder Released"));
}
void AfsCharacter::doLeftTriggerPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Left Trigger Pressed"));
	switch(CharacterMode)
    {
        case 0://melee
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Melee"));
			if(MeleeWeapon)MeleeWeapon->OnLeftTriggerPressed();
            break;
        case 1://gun
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Ranged"));
			if(RangedWeapon)RangedWeapon->OnLeftTriggerPressed();
            break;
        case 2://magic or special
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Magic"));
            break;
    }
}
void AfsCharacter::doLeftTriggerReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Left Trigger Released"));
	switch(CharacterMode)
    {
        case 0://melee
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Melee"));
			if(MeleeWeapon)MeleeWeapon->OnLeftTriggerReleased();
            break;
        case 1://gun
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Ranged"));
			if(RangedWeapon)RangedWeapon->OnLeftTriggerReleased();
            break;
        case 2://magic or special
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Magic"));
            break;
    }
}
void AfsCharacter::doFaceTopPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Face Top Pressed"));
    GetWorldTimerManager().SetTimer(SwitchTimer,this,&AfsCharacter::SwitchCold,SwitchDelay,false);
}
void AfsCharacter::doFaceTopReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Face Top Released"));
	if(GetWorldTimerManager().GetTimerRemaining(SwitchTimer)!=-1.0f)
	{
		GetWorldTimerManager().ClearTimer(SwitchTimer);
		switch(CharacterMode)
    	{
    	    case 0://melee
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Ranged"));
    	        CharacterMode = 1;
    	        break;
    	    case 1://gun
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Melee"));
    	        CharacterMode = 0;
    	        break;
    	    case 2://magic or special
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Melee"));
    	        CharacterMode = 0;
    	        break;
    	}
	}
}
void AfsCharacter::doFaceRightPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Face Right Pressed"));
}
void AfsCharacter::doFaceRightReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Face Right Released"));
}
void AfsCharacter::doFaceBottomPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Face Bottom Pressed"));
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
void AfsCharacter::doFaceBottomReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Face Bottom Released"));
}
void AfsCharacter::doFaceLeftPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Face Left Pressed"));
}
void AfsCharacter::doFaceLeftReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Face Left Released"));
}
void AfsCharacter::doDpadUpPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("D-pad Up Pressed"));
}
void AfsCharacter::doDpadUpReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("D-pad Up Released"));
}
void AfsCharacter::doDpadRightPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("D-pad Right Pressed"));
}
void AfsCharacter::doDpadRightReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("D-pad Right Released"));
}
void AfsCharacter::doDpadDownPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("D-pad Down Pressed"));
}
void AfsCharacter::doDpadDownReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("D-pad Down Released"));
}
void AfsCharacter::doDpadLeftPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("D-pad Left Pressed"));
}
void AfsCharacter::doDpadLeftReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("D-pad Left Released"));
}
void AfsCharacter::doRightStickPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Right Stick Pressed"));
}
void AfsCharacter::doRightStickReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Right Stick Released"));
}
void AfsCharacter::doLeftStickPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Left Stick Pressed"));
}
void AfsCharacter::doLeftStickReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Left Stick Released"));
}

void AfsCharacter::SwitchCold()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Switch timeout, Long Press."));
    switch(CharacterMode)
    {
        case 0://melee
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Magic"));
            CharacterMode = 2;
            break;
        case 1://gun
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Magic"));
            CharacterMode = 2;
            break;
        case 2://magic or special
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("character mode Ranged"));
            CharacterMode = 1;
            break;
    }
}

void AfsCharacter::MeleeCold()
{
    MeleeAllowed = true;
    //GetWorldTimerManager().ClearTimer(MeleeTimer); unnecessary because of false repeat flag.
}

void AfsCharacter::Landed(const FHitResult &Hit)
{
    Super::Landed(Hit);
    JumpVal = 0;
}
