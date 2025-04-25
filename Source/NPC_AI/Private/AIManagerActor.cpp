// AIManagerActor.cpp
#include "AIManagerActor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

AAIManagerActor::AAIManagerActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

bool AAIManagerActor::IsValidSpawnLocation(FVector Location)
{
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Location,
        Location + FVector(0.f, 0.f, 100.f),
        ECC_Visibility,
        CollisionParams
    );

    DrawDebugLine(GetWorld(), Location, Location + FVector(0.f, 0.f, 100.f),
                bHit ? FColor::Red : FColor::Green, false, 2.0f, 0, 1.0f);

    return !bHit;
}