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
    FTimerHandle RangedSkillTimer;
    FTimerHandle MeleeSkillTimer;
    FTimerHandle ShotTimer;
    FTimerHandle RangedRechargeTimer;
    FTimerHandle MeleeRechargeTimer;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float MeleeLightCooldown = .2f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float MeleeHeavyCooldown = .4f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float MeleeSkillCooldown = 1.0f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float RangedSkillCooldown = 1.0f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float ShotCooldown = .1f;//could change this to be interpreted as shots/second
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float RangedHeatIncrement = .1f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float RangedOverHeat = .1f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float MeleeOverHeat = .1f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float WeaponMeleeOverHeatMultiple= 2.f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    float WeaponRangedOverHeatMultiple= 2.f;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
	bool AutomaticFire = false;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    bool IsMelee=true;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    UAnimMontage* astMeleeHvy;
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "WeaponProperties")
    UAnimMontage* astMeleeLgt;

	bool InIronSights = false;
	bool CanFire = true;
	bool CanMelee= true;
	bool ShotFlag = true;
	bool MeleeFlag = true;
	bool MeleeSkillColdFlag = true;
	bool RangedSkillColdFlag = true;
	float HeatIncrement = 0.f;
    
    virtual void StartFire();
    virtual void StopFire();
	virtual void FeatherPrevention();
    virtual void IncreaseMeleeHeat();
    virtual void IncreaseRangedHeat();
    virtual void Fire();
    virtual void RangedSkill();
    virtual void MeleeHvy();
    virtual void MeleeLgt();
    virtual void MeleeSkill();
	virtual void EnterIronSights();
	virtual void LeaveIronSights();
	virtual void MeleeWeaponCold();
	virtual void RangedWeaponCold();
	virtual void RangedSkillCold();
	virtual void MeleeSkillCold();
    
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
