// Fill out your copyright notice in the Description page of Project Settings.

#include "FourSouls.h"
#include "fsMeleeWeapon.h"

// Sets default values for this actor's properties
AfsMeleeWeapon::AfsMeleeWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	MeleeLightCooldown = 0.2f;
	MeleeHeavyCooldown = 0.4f;
	ShotCooldown = 0.1f;
	HeatIncrement = 0.1f;
	OverHeat = 10.f;
	IsMelee = true;
	SkillColdFlag = true;
	ShotFlag = true;
	CanFire = true;
	WeaponOverHeatMultiple = 0.1f;
}

//FTimer MeleeTimer;
//FTimer ShotTimer;
//FTimer RechargeTimer;
//FTimer SkillTimer;

void AfsMeleeWeapon::IncreaseHeat()
{
	Super::IncreaseHeat();
	if (CanFire)
	{
		float Heat = GetWorldTimerManager().GetTimerRemaining(RechargeTimer);
		GetWorldTimerManager().ClearTimer(RechargeTimer);
		Heat += HeatIncrement;
		if (Heat >= OverHeat)
		{
			GetWorldTimerManager().SetTimer(RechargeTimer, this, &AfsMeleeWeapon::WeaponCold, WeaponOverHeatMultiple*OverHeat, false);
			CanFire = false;
		}
		else
		{
			GetWorldTimerManager().SetTimer(RechargeTimer, this, &AfsMeleeWeapon::WeaponCold, Heat, false);
		}
		ShotFlag = true;
	}
}
void AfsMeleeWeapon::MeleeHvy()
{		
	if (ShotFlag & CanFire)
	{
		ShotFlag = false;
		Super::MeleeHvy();
		HeatIncrement = MeleeHeavyCooldown * 2;//obviously, all of these are just to demonstrate the capabilities of the current weapon architecture, they can be changed dramatically.
		if(Player)Player->PlayAnimMontage(astMeleeHvy);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Heavy attack"));
		//having heat on melee weapons could be interesting though.
		GetWorldTimerManager().SetTimer(MeleeTimer, this, &AfsMeleeWeapon::IncreaseHeat, MeleeHeavyCooldown, false);
	}
}
void AfsMeleeWeapon::MeleeLgt()
{
	if (ShotFlag & CanFire)
	{
		ShotFlag = false;
		Super::MeleeLgt();
		HeatIncrement = MeleeLightCooldown * 2;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("light attack"));
		if(Player)Player->PlayAnimMontage(astMeleeLgt);
		GetWorldTimerManager().SetTimer(MeleeTimer, this, &AfsMeleeWeapon::IncreaseHeat, MeleeLightCooldown, false);
	}
}
void AfsMeleeWeapon::MeleeSkill()
{
	if (SkillColdFlag)
	{
		SkillColdFlag = false;
		Super::MeleeSkill();
		GetWorldTimerManager().SetTimer(SkillTimer, this, &AfsWeapon::SkillCold, SkillCooldown, false);
	}
}
void AfsMeleeWeapon::SkillCold()
{
	SkillColdFlag = true;
}
void AfsMeleeWeapon::WeaponCold()
{
	CanFire = true;
	ShotFlag = true;
}

//up to three weapon abilities per weapon
void AfsMeleeWeapon::OnLeftTriggerPressed()
{
	Super::OnLeftTriggerPressed();
	MeleeSkill();
}
void AfsMeleeWeapon::OnLeftTriggerReleased()
{
	Super::OnLeftTriggerReleased();
}
void AfsMeleeWeapon::OnRightTriggerPressed()
{
	Super::OnRightTriggerPressed();
	MeleeHvy();
}
void AfsMeleeWeapon::OnRightTriggerReleased()
{
	Super::OnRightTriggerReleased();
}
void AfsMeleeWeapon::OnRightShoulderPressed()
{
	Super::OnRightShoulderPressed();
	MeleeLgt();
}
void AfsMeleeWeapon::OnRightShoulderReleased()
{
	Super::OnRightShoulderReleased();
}
//called when put into main slot using D-pad
void AfsMeleeWeapon::OnEquip(AfsCharacter* player)
{
	Super::OnEquip(player);
}
void AfsMeleeWeapon::OnDeequip()
{
	Super::OnDeequip();
}
//called when readied/unreadied
void AfsMeleeWeapon::OnReady()
{
	Super::OnReady();
}
void AfsMeleeWeapon::OnSwitch()
{
	Super::OnSwitch();
}
void AfsMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
}
	// Called every frame
void AfsMeleeWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}