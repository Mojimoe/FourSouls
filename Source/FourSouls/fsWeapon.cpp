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
}
void AfsWeapon::StopFire()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Stop Fire"));
}
void AfsWeapon::IncreaseHeat()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Increase Heat"));
}
void AfsWeapon::Fire()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Fire"));
}
void AfsWeapon::RangedSkill()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Ranged Skill"));
}
void AfsWeapon::MeleeHvy()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Melee Heavy"));
}
void AfsWeapon::MeleeLgt()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Melee Light"));
}
void AfsWeapon::MeleeSkill()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Melee Skill"));
}
void AfsWeapon::EnterIronSights()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Enter Iron Sights"));
}
void AfsWeapon::LeaveIronSights()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Leave Iron Sights"));
}
void AfsWeapon::WeaponCold()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Cold"));
}
void AfsWeapon::SkillCold()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Skill Cold"));
}

//up to three weapon abilities per weapon
void AfsWeapon::OnLeftTriggerPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Left Trigger Pressed"));
}
void AfsWeapon::OnLeftTriggerReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Left Trigger Released"));
}
void AfsWeapon::OnRightTriggerPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Trigger Pressed"));
}
void AfsWeapon::OnRightTriggerReleased()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Trigger Released"));
}
void AfsWeapon::OnRightShoulderPressed()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Weapon Right Shoulder Pressed"));
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