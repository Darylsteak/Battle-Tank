// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Turret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Math/Vector.h"
#include "BattleTank.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	//So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName ("Shell"));
	bool bhaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bhaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("aiming solution found"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No aiming solution found"));
	}

	//if no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	//Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.GetNormalized().Pitch);

	//Always yaw the shortest way
	if(DeltaRotator.GetNormalized().Yaw < 180)
	{
		Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.GetNormalized().Yaw);
	}

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); 
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (Ammo <= 0)
	{
		FiringStatus = EFiringStatus::Empty;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}


int UTankAimingComponent::GetAmmoLeft() const
{
	return Ammo;
}


void UTankAimingComponent::Fire()
{
	if (FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::Empty)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Shell")),
			Barrel->GetSocketRotation(FName("Shell"))
			);

		Ammo = Ammo - 1;

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

