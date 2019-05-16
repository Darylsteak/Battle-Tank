// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));

	if (GetControlledTank() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Have possesed a tank: %s"), *GetControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Have not possesed a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //OUT Parameter
	if (GetSightRayHitLocation(HitLocation)) //Will line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString()); 
		// TODO control tank to aim at this point
	}

	//Get world location through crosshair thru linetrace, return true if hits landscape	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D( ViewportSizeX * CrossHairXLocation , ViewportSizeY * CrossHairYLocation );

	//remov sanic fast
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	//"De-project" the screen position of the crosshair to a world collision
	//Line trace along that and see what we hit (up to certain range)
	OutHitLocation = FVector(1.0);
	return true;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
