// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIcontroller.h"
#include "Tank.h"

void ATankAIcontroller::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIcontroller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//Aim at player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	
		//Fire
		ControlledTank->Fire(); //TODO Dont fire every frame (limit firing rate)
	}
}
