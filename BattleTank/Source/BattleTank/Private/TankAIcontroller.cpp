// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIcontroller.h"

void ATankAIcontroller::BeginPlay()
{
	Super::BeginPlay();

	if (GetPlayerTank() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIcontroller has detected a player controlled tank: %s"), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIcontroller has not detected a player controlled tank"));
	}
}

ATank* ATankAIcontroller::GetControlledTank() const { return Cast<ATank>(GetPawn()); }

ATank * ATankAIcontroller::GetPlayerTank() const 
{ 
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);
}
