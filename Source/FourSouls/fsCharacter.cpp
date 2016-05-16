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
    InputComponent->BindAction("MeleeLgt",IE_Pressed,this,&AfsCharacter::doMeleeLgt);
    InputComponent->BindAxis("Player_X",this,&AfsCharacter::MoveX);
    InputComponent->BindAxis("Player_Y",this,&AfsCharacter::MoveY);
    InputComponent->BindAxis("Player_Yaw",this,&AfsCharacter::AddControllerYawInput);
    InputComponent->BindAxis("Player_Pitch",this,&AfsCharacter::AddControllerPitchInput);
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
        GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,TEXT("001"));
        PlayAnimMontage(astMeleeLgt);
        GetWorldTimerManager().SetTimer(MeleeTimer,this,&AfsCharacter::MeleeCold,1.0f,false);
    }
}