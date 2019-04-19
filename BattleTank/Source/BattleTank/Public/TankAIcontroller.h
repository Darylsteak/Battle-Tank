// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankAIcontroller.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIcontroller : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

private:

	ATank* GetPlayerTank() const;
	
};
