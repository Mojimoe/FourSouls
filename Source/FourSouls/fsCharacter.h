// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "fsCharacter.generated.h"

UCLASS()
class FOURSOULS_API AfsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    bool MeleeAllowed = true;
    bool SwitchAllowed = true;
    FTimerHandle MeleeTimer;
    FTimerHandle SwitchTimer;
    void MeleeCold();
	int JumpVal = 0;
    int CharacterMode = 0;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "SwitchDelay")
    float SwitchDelay = .1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JumpVelocity")
    float JumpVelocity = 800.0f;
    
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Melee")
    UAnimMontage* astMeleeLgt;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Melee")
	float LightDelay=0.3f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Melee")
    UAnimMontage* astMeleeHvy;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Melee")
    float HeavyDelay=0.6f;

    
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "carm")
    USpringArmComponent* PlayerCameraArm;
    
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "cam")
    UCameraComponent* PlayerCamera;
    
	// Sets default values for this character's properties
	AfsCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    void MoveX(float in);
    void MoveY(float in);
    
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None) override;
    
    virtual void doMeleeLgt();
    virtual void doMeleeHvy();

	virtual void doJump();

	virtual void Landed(const FHitResult &Hit) override;
	void AddControllerYawInputGP(float in);
	void AddControllerPitchInputGP(float in);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ControllerSensitivity")
	float PitchSensitivity = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ControllerSensitivity")
	float YawSensitivity = 2.0f;
    void CharacterModeChange();
    void SwitchCold();
    void doRightShoulder();
    void doRightTrigger();
};
