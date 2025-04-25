#include "AIBoundaryVolume.h"

AAIBoundaryVolume::AAIBoundaryVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	
	BoundaryBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundaryBox"));
	RootComponent = BoundaryBox;
	BoundaryBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoundaryBox->SetBoxExtent(FVector(5000, 5000, 100));
}

FVector AAIBoundaryVolume::GetRandomPointInVolume() const
{
	return FMath::RandPointInBox(BoundaryBox->Bounds.GetBox());
}