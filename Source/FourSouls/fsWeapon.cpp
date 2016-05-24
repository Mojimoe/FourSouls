// Fill out your copyright notice in the Description page of Project Settings.

#include "FourSouls.h"
#include "fsWeapon.h"

// Sets default values
AfsWeapon::AfsWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AfsWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AfsWeapon::Tick( float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );
}

void AfsWeapon::StartFire()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Start Fire"));
	GetWorldTimerManager().ClearTimer(ShotTimer);
	Fire();
	GetWorldTimerManager().SetTimer(ShotTimer, this, &AfsWeapon::Fire, ShotCooldown, true);
	//the shot timer utility and the shotflag should be removed from the fire function, since it's handled up here as a repeating timer.
}
void AfsWeapon::StopFire()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Stop Fire"));
	GetWorldTimerManager().ClearTimer(ShotTimer);
	if (GetWorldTimerManager().GetTimerRemaining(FeatherTimer) == -1.0f)
	{
		ShotFlag = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("FeatherTimer Start"));
		GetWorldTimerManager().SetTimer(FeatherTimer, this, &AfsWeapon::FeatherPrevention, ShotCooldown, false);
	}
}
void AfsWeapon::FeatherPrevention()
{
	//same as RangedWeaponCold, but only clears ShotFlag. used to prevent user from feathering trigger to fire once per trigger shot using startfire
	//if it also cleared CanFire, then people would have to wait 1 shot time to clear overheat lockout, even though it would only fire one time.
	//the increaseheat functions could also be written such that they would be the functions that fire off the animations and bullets and such, 
	//so if placed within the overheat check, would make this unnecessary, but would also maybe reset the overheat timer every time you pull the trigger
	//which also doesnt work.  This is likely the best solution.
	//
	//there could be a different architecture based on automatic fire rather than single fire that might work better, but that's a problem for a later time.
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("FeatherPrevention"));
	ShotFlag = true;
}
void AfsWeapon::IncreaseMeleeHeat()
{
	if (CanMelee)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Increase Heat"));
		float Heat = GetWorldTimerManager().GetTimerRemaining(MeleeRechargeTimer);
		GetWorldTimerManager().ClearTimer(MeleeRechargeTimer);
		Heat += HeatIncrement;
		if (Heat >= MeleeOverHeat)
		{
			GetWorldTimerManager().SetTimer(MeleeRechargeTimer, this, &AfsWeapon::MeleeWeaponCold, WeaponMeleeOverHeatMultiple*MeleeOverHeat, false);
			CanMelee = false;
		}
		else
		{
			GetWorldTimerManager().SetTimer(MeleeRechargeTimer, this, &AfsWeapon::MeleeWeaponCold, Heat, false);
		}
		MeleeFlag = true;
	}
}
void AfsWeapon::IncreaseRangedHeat()
{
	if (CanFire)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Increase Heat"));
		float Heat = GetWorldTimerManager().GetTimerRemaining(RangedRechargeTimer);
		GetWorldTimerManager().ClearTimer(RangedRechargeTimer);
		Heat += HeatIncrement;
		if (Heat >= RangedOverHeat)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("OVERHEAT"));
			GetWorldTimerManager().SetTimer(RangedRechargeTimer, this, &AfsWeapon::RangedWeaponCold, WeaponRangedOverHeatMultiple*RangedOverHeat, false);
			CanFire = false;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("WARMING"));
			GetWorldTimerManager().SetTimer(RangedRechargeTimer, this, &AfsWeapon::RangedWeaponCold, Heat, false);
		}
		ShotFlag = true;
	}
}
void AfsWeapon::Fire()
{
	if (AutomaticFire & CanFire & ShotFlag)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("AutomaticFire"));
		HeatIncrement = RangedHeatIncrement;
		IncreaseRangedHeat();
	}
	else if (!AutomaticFire & CanFire & ShotFlag)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("SingleFire"));
		ShotFlag = false;
		HeatIncrement = RangedHeatIncrement;
		GetWorldTimerManager().SetTimer(ShotTimer, this, &AfsWeapon::IncreaseRangedHeat, ShotCooldown, false);
	}
}
void AfsWeapon::RangedSkill()
{
	if (RangedSkillColdFlag)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Ranged Skill"));
		RangedSkillColdFlag = false;
		GetWorldTimerManager().SetTimer(RangedSkillTimer, this, &AfsWeapon::RangedSkillCold, RangedSkillCooldown, false);
	}
}
void AfsWeapon::MeleeHvy()
{
	if (MeleeFlag & CanMelee)
	{
		MeleeFlag = false;
		HeatIncrement = MeleeHeavyCooldown * 2;//obviously, all of these are just to demonstrate the capabilities of the current weapon architecture, they can be changed dramatically.
		if (Player)
		{
			UCharacterMovementComponent *charmov = Player->GetCharacterMovement();
			if (charmov->MovementMode == MOVE_Walking)
			{
				Player->PlayAnimMontage(astMeleeHvy);
			}
			else
			{
				Player->PlayAnimMontage(astMeleeHvyAir);
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Melee Heavy"));
		//having heat on melee weapons could be interesting though.
		GetWorldTimerManager().SetTimer(MeleeTimer, this, &AfsWeapon::IncreaseMeleeHeat, MeleeHeavyCooldown, false);
	}
}
void AfsWeapon::MeleeLgt()
{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("FSWEAPON_WORKING"));
	if (MeleeFlag & CanMelee)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Melee Light"));
		MeleeFlag = false;
		HeatIncrement = MeleeLightCooldown * 2;
		if (Player)
		{
			UCharacterMovementComponent *charmov = Player->GetCharacterMovement();
			if (charmov->MovementMode == MOVE_Walking)
			{
				Player->PlayAnimMontage(astMeleeLgt);
			}
			else
			{
				Player->PlayAnimMontage(astMeleeLgtAir);
			}
		}
		GetWorldTimerManager().SetTimer(MeleeTimer, this, &AfsWeapon::IncreaseMeleeHeat, MeleeLightCooldown, false);
	}
}
void AfsWeapon::MeleeSkill()
{
	if (MeleeSkillColdFlag)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Melee Skill"));
		MeleeSkillColdFlag = false;
		GetWorldTimerManager().SetTimer(MeleeSkillTimer, this, &AfsWeapon::MeleeSkillCold, MeleeSkillCooldown, false);
	}
}
void AfsWeapon::EnterIronSights()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Enter Iron Sights"));
	InIronSights = true;
}
void AfsWeapon::LeaveIronSights()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Leave Iron Sights"));
	InIronSights = false;
}
void AfsWeapon::MeleeWeaponCold()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Cold"));
	CanMelee = true;
	MeleeFlag = true;
}
void AfsWeapon::RangedWeaponCold()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Cold"));
	CanFire = true;
	ShotFlag = true;
}
void AfsWeapon::MeleeSkillCold()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Melee Skill Cold"));
	MeleeSkillColdFlag = true;
}
void AfsWeapon::RangedSkillCold()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Ranged Skill Cold"));
	RangedSkillColdFlag = true;
}

//up to three weapon abilities per weapon
void AfsWeapon::OnLeftTriggerPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Left Trigger Pressed"));
	if (IsMelee)
	{
		MeleeSkill();
	}
	else
	{
		EnterIronSights();
	}
}
void AfsWeapon::OnLeftTriggerReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Left Trigger Released"));
	if (InIronSights)
	{
		LeaveIronSights();
	}
}
void AfsWeapon::OnRightTriggerPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Trigger Pressed"));
	if (IsMelee)
	{
		MeleeHvy();
	}
	else if(AutomaticFire)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Trigger Pressed Pre-Startfire"));
		StartFire();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Trigger Pressed Pre-Singlefire"));
		Fire();
	}
}
void AfsWeapon::OnRightTriggerReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Trigger Released"));
	if (!IsMelee & AutomaticFire)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Trigger Released Pre-Stopfire"));
		StopFire();
	}
}
void AfsWeapon::OnRightShoulderPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Shoulder Pressed"));
	if (IsMelee)
	{
		MeleeLgt();
	}
	else
	{
		RangedSkill();
	}
}
void AfsWeapon::OnRightShoulderReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Shoulder Released"));
}
//called when put into main slot using D-pad
void AfsWeapon::OnEquip(AfsCharacter* player)
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Equipped"));
	Player = player;
}
void AfsWeapon::OnDeequip()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Deequpped"));
}
//called when readied/unreadied
void AfsWeapon::OnReady()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Readied"));
}
void AfsWeapon::OnSwitch()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Unreadied"));
}