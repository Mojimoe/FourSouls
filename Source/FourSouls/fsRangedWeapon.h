// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "fsWeapon.h"
#include "fsCharacter.h"
#include "fsRangedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FOURSOULS_API AfsRangedWeapon : public AfsWeapon
{
	GENERATED_BODY()
public:

	AfsRangedWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void IncreaseHeat() override;
    virtual void Fire() override;
    virtual void RangedSkill() override;
	virtual void EnterIronSights() override;
	virtual void LeaveIronSights() override;
	virtual void WeaponCold() override;
	virtual void SkillCold() override;
    
    //up to three weapon abilities per weapon
    virtual void OnLeftTriggerPressed() override;
    virtual void OnLeftTriggerReleased() override;
    virtual void OnRightTriggerPressed() override;
    virtual void OnRightTriggerReleased() override;
    virtual void OnRightShoulderPressed() override;
    virtual void OnRightShoulderReleased() override;
    //called when put into main slot using D-pad
    virtual void OnEquip(AfsCharacter* player) override;
    virtual void OnDeequip() override;
    //called when readied/unreadied
    virtual void OnReady() override;
    virtual void OnSwitch() override;
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
