// Fill out your copyright notice in the Description page of Project Settings.

#include "FourSouls.h"
#include "fsRangedWeapon.h"

// Sets default values for this actor's properties
AfsRangedWeapon::AfsRangedWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	SkillCooldown = 1.0f;
	ShotCooldown = .1f;//could change this to be interpreted as shots/second
	HeatIncrement = .2f;
	OverHeat = 1.f;
	IsMelee=false;
	AutomaticFire = false;
	CanFire = true;
	ShotFlag = true;
    WeaponOverHeatMultiple= 2.f;
}

//FTimer RangedSkillTimer;
//FTimer ShotTimer;
//FTimer RechargeTimer;

void AfsRangedWeapon::StartFire()
{
	Super::StartFire();
	//GetWorldTimermanager().SetTimer(ShotTimer, this, &AfsRangedWeapon::Fire, ShotCooldown, true);
	//the shot timer utility and the shotflag should be removed from the fire function, since it's handled up here as a repeating timer.
}
void AfsRangedWeapon::StopFire()
{
	Super::StopFire();
	//GetWorldTimermanager().ClearTimer(ShotTimer);
	//ShotFlag = false;
	//GetWorldTimermanager().SetTimer(ShotTimer, this, &AfsRangedWeapon::WeaponCold, ShotCooldown, true);
	//this would need a bit of work, what needs preventing is feathering the trigger to fire faster than the full auto allows.
	//the above would work, but would clear the CanFire flag, and would reset the overheat, which shouldn't happen
}
void AfsRangedWeapon::IncreaseHeat()
{
	Super::IncreaseHeat();
	if (CanFire)
	{
		float Heat = GetWorldTimerManager().GetTimerRemaining(RechargeTimer);
		GetWorldTimerManager().ClearTimer(RechargeTimer);
		Heat += HeatIncrement;
		if (Heat >= OverHeat)
		{
			GetWorldTimerManager().SetTimer(RechargeTimer, this, &AfsRangedWeapon::WeaponCold, WeaponOverHeatMultiple*OverHeat, false);
			CanFire = false;
		}
		else
		{
			GetWorldTimerManager().SetTimer(RechargeTimer, this, &AfsRangedWeapon::WeaponCold, Heat, false);
		}
		ShotFlag = true;
	}
}
void AfsRangedWeapon::Fire()
{
	if (CanFire & ShotFlag)
	{
		Super::Fire();
		ShotFlag = false;
		GetWorldTimerManager().SetTimer(ShotTimer, this, &AfsRangedWeapon::IncreaseHeat, ShotCooldown, false);
	}
}
void AfsRangedWeapon::RangedSkill()
{
	if (SkillColdFlag)
	{
		Super::RangedSkill();
		SkillColdFlag = false;
		GetWorldTimerManager().SetTimer(SkillTimer, this, &AfsRangedWeapon::SkillCold, SkillCooldown, false);
	}
}
void AfsRangedWeapon::EnterIronSights()
{
	Super::EnterIronSights();
	InIronSights = true;
	//do camera manipulations
}
void AfsRangedWeapon::LeaveIronSights()
{
	Super::LeaveIronSights();
	InIronSights = false;
	//do camera manipulations
}
void AfsRangedWeapon::WeaponCold()
{
	CanFire = true;
	ShotFlag = true;
}
void AfsRangedWeapon::SkillCold()
{
	Super::SkillCold();
	SkillColdFlag = true;
}

//up to three weapon abilities per weapon
void AfsRangedWeapon::OnLeftTriggerPressed()
{
	Super::OnLeftTriggerPressed();
	EnterIronSights();
}
void AfsRangedWeapon::OnLeftTriggerReleased()
{
	Super::OnLeftTriggerReleased();
	LeaveIronSights();
}
void AfsRangedWeapon::OnRightTriggerPressed()
{
	Super::OnRightTriggerPressed();
	if (AutomaticFire)
	{
		StartFire();
	}
	else
	{
		Fire();
	}
}
void AfsRangedWeapon::OnRightTriggerReleased()
{
	Super::OnRightTriggerReleased();
	if (AutomaticFire)
	{
		StopFire();
	}
}
void AfsRangedWeapon::OnRightShoulderPressed()
{
	Super::OnRightShoulderPressed();
	RangedSkill();
}
void AfsRangedWeapon::OnRightShoulderReleased()
{
	Super::OnRightShoulderReleased();
}
//called when put into main slot using D-pad
void AfsRangedWeapon::OnEquip(AfsCharacter* player)
{
	Super::OnEquip(player);
}
void AfsRangedWeapon::OnDeequip()
{
	Super::OnDeequip();
}
//called when readied/unreadied
void AfsRangedWeapon::OnReady()
{
	Super::OnReady();
}
void AfsRangedWeapon::OnSwitch()
{
	Super::OnSwitch();
}
	// Called when the game starts or when spawned
void AfsRangedWeapon::BeginPlay()
{
	Super::BeginPlay();
}
	// Called every frame
void AfsRangedWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}