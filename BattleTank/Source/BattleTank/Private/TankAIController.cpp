// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "Engine/World.h" 

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
	}
	else
	{
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		FVector OurTankLocation = GetPlayerTank()->GetActorLocation();
		GetControlledTank()->AimAt(OurTankLocation);
		FString OurTankName = GetControlledTank()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at  %s"), *OurTankName, *OurTankLocation.ToString())
	}

}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
