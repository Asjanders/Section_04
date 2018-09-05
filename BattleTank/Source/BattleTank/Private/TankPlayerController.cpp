// Fill out your copyright notice in the Description page of Project Settings.



#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	ATank* ControlledTank = GetControlledTank();
	Super::BeginPlay();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController: No Controlled Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController: Begin Play: %s"), *(ControlledTank->GetName()));

	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return;}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraScreenLocation;
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraScreenLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}