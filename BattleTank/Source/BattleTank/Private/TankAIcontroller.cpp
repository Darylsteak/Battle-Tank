// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIcontroller.h"
#include "TankAimingComponent.h"

void ATankAIcontroller::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIcontroller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	//Move Towards Player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim at player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	//Fire
	AimingComponent->Fire();
	
}
