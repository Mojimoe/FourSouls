// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "fsCharacter.generated.h"

class AfsWeapon;

UCLASS()
class FOURSOULS_API AfsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    //character timers. melee timer can either be moved to weapon class (likely) or kept as ingame class specific.
    FTimerHandle MeleeTimer;
    FTimerHandle SwitchTimer;

	AfsWeapon* MeleeWeapon=nullptr;
	AfsWeapon* RangedWeapon=nullptr;

    //character state booleans
    bool MeleeAllowed = true;
    bool SwitchAllowed = true;
	bool Sprinting = false;

    //character state integers
    int JumpVal = 0;
    int CharacterMode = 0;
	
    //delays, cooldowns, and sensitivities. heavy and light delay will be switched to weapon class. TODO
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "SwitchDelay")
    float SwitchDelay = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "JumpVelocity")
    float JumpVelocity = 800.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SprintSpeedMultiplier")
    float SprintSpeedMultiplierForward= 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SprintSpeedMultiplier")
    float SprintSpeedMultiplierSideways= 1.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Melee")
	float LightDelay=0.3f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Melee")
    float HeavyDelay=0.6f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ControllerSensitivity")
    float PitchSensitivity = 2.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ControllerSensitivity")
    float YawSensitivity = 2.0f;
    
    //animation montages specified on character. this will be moved to the weapon class. TODO
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Roll")
    UAnimMontage* ForwardRoll;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Roll")
    UAnimMontage* RightRoll;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Roll")
    UAnimMontage* BackRoll;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Roll")
    UAnimMontage* LeftRoll;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Melee")
    UAnimMontage* astMeleeHvy;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Melee")
    UAnimMontage* astMeleeLgt;

    //camera components
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "carm")
    USpringArmComponent* PlayerCameraArm;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "cam")
    UCameraComponent* PlayerCamera;
    
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AfsWeapon> MeleeWeaponToSpawn;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AfsWeapon> RangedWeaponToSpawn;
    
	// Sets default values for this character's properties
	AfsCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    //movement input functions
    virtual void MoveX(float in);
    virtual void MoveY(float in);
    virtual void AddControllerYawInputGP(float in);
    virtual void AddControllerPitchInputGP(float in);
    
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    //generic for playing animations
    virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None) override;
    
    //original melee functions
    virtual void doMeleeLgt();
    virtual void doMeleeHvy();
    //input handling functions
    virtual void doRightShoulderPressed();
    virtual void doRightShoulderReleased();
    virtual void doRightTriggerPressed();
    virtual void doRightTriggerReleased();
    virtual void doLeftShoulderPressed();
    virtual void doLeftShoulderReleased();
    virtual void doLeftTriggerPressed();
    virtual void doLeftTriggerReleased();
    virtual void doFaceTopPressed();
    virtual void doFaceTopReleased();
    virtual void doFaceRightPressed();
    virtual void doFaceRightReleased();
    virtual void doFaceBottomPressed();
    virtual void doFaceBottomReleased();
    virtual void doFaceLeftPressed();
    virtual void doFaceLeftReleased();
    virtual void doDpadUpPressed();
    virtual void doDpadUpReleased();
    virtual void doDpadRightPressed();
    virtual void doDpadRightReleased();
    virtual void doDpadDownPressed();
    virtual void doDpadDownReleased();
    virtual void doDpadLeftPressed();
    virtual void doDpadLeftReleased();
    virtual void doRightStickPressed();
    virtual void doRightStickReleased();
    virtual void doLeftStickPressed();
    virtual void doLeftStickReleased();

    //end of cooldown functions
    virtual void SwitchCold();
    virtual void MeleeCold();
    
    //character landing
	virtual void Landed(const FHitResult &Hit) override;
};
