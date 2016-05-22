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
    
	AfsCharacter* Player;
    FTimerHandle MeleeTimer;
    FTimerHandle SkillTimer;
    FTimerHandle ShotTimer;
    FTimerHandle RechargeTimer;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float MeleeLightCooldown = .2f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float MeleeHeavyCooldown = .4f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float SkillCooldown = 1.0f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float ShotCooldown = .1f;//could change this to be interpreted as shots/second
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float HeatIncrement = .1f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float OverHeat = .1f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float WeaponOverHeatMultiple= 2.f;

    bool IsMelee=true;
	bool InIronSights = false;
	bool AutomaticFire = false;
	bool CanFire = true;
	bool ShotFlag = true;
	bool SkillColdFlag = true;
    
    virtual void StartFire();
    virtual void StopFire();
    virtual void IncreaseHeat();
    virtual void Fire();
    virtual void RangedSkill();
    virtual void MeleeHvy();
    virtual void MeleeLgt();
    virtual void MeleeSkill();
	virtual void EnterIronSights();
	virtual void LeaveIronSights();
	virtual void WeaponCold();
	virtual void SkillCold();
    
    //up to three weapon abilities per weapon
    virtual void OnLeftTriggerPressed();
    virtual void OnLeftTriggerReleased();
    virtual void OnRightTriggerPressed();
    virtual void OnRightTriggerReleased();
    virtual void OnRightShoulderPressed();
    virtual void OnRightShoulderReleased();
    //called when put into main slot using D-pad
    virtual void OnEquip(AfsCharacter* player);
    virtual void OnDeequip();
    //called when readied/unreadied
    virtual void OnReady();
    virtual void OnSwitch();
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
