// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine//World.h"
#include "TankAIcontroller.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIcontroller : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:

	//How close the AI tank get to the player
	float AcceptanceRadius = 3000;
	
};
