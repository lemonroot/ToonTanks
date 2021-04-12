// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{

}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    // Telling the world timer to create a new timer.
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    // Finds player pawn to see if it exists in world.
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition() 
{
    if(!PlayerPawn)
    {
        return;
    }
    if(ReturnDistanceToPlayer() <= FireRange)
    {
        UE_LOG(LogTemp, Warning, TEXT("Fire condition success."));
    }
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn)
    {
        return 0.f;
    }

    // Gets distance between player and this actor's location.
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation()); 
}