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

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:

	//How close the AI tank get to the player
	UPROPERTY(EditAnywhere, Category = "Setup") //Consider EditDefaultsOnly
	float AcceptanceRadius = 3000;
	
};
