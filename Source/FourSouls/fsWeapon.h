// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "fsCharacter.h"
#include "fsWeapon.generated.h"

UCLASS()
class FOURSOULS_API AfsWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AfsWeapon();
    
    FTimer MeleeTimer;
    FTimer RangedSkillTimer;
    FTimer ShotTimer;
    FTimer RechargeTimer;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float MeleeLightCooldown = .2f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float MeleeHeavyCooldown = .4f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float RangedSkillCooldown = 1.0f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float ShotCooldown = .1f;//could change this to be interpreted as shots/second
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float HeatIncrement = .1f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float OverHeat = .1f;

    bool IsMelee=true;
    
    virtual void StartFire();
    virtual void StopFire();
    virtual void IncreaseHeat();
    virtual void Fire();
    virtual void RangedSkill();
    virtual void MeleeHvy();
    virtual void MeleeLgt();
    virtual void MeleeSkill();
    
    //up to three weapon abilities per weapon
    virtual void OnLeftTriggerPressed();
    virtual void OnLeftTriggerReleased();
    virtual void OnRightTriggerPressed();
    virtual void OnRightTriggerReleased();
    virtual void OnRightShoulderPressed();
    virtual void OnRightShoulderReleased();
    //called when put into main slot using D-pad
    virtual void OnEquip();
    virtual void OnDeequip();
    //called when readied/unreadied
    virtual void OnReady();
    virtual void OnSwitch();
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
