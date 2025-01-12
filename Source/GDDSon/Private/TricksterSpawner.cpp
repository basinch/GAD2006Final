#include "TricksterSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

ATricksterSpawner::ATricksterSpawner()
{
    PrimaryActorTick.bCanEverTick = true;

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    RootComponent = SpawnArea;

    SpawnInterval = 5.0f;
}

void ATricksterSpawner::BeginPlay()
{
    Super::BeginPlay();

    if (BlueprintToSpawn)
    {
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ATricksterSpawner::SpawnBlueprint, SpawnInterval, true);
    }
}

void ATricksterSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

FVector ATricksterSpawner::GetRandomPointInBox() const
{
    FVector Origin = SpawnArea->Bounds.Origin;
    FVector Extent = SpawnArea->GetScaledBoxExtent();
    return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}

void ATricksterSpawner::SpawnBlueprint()
{
    if (BlueprintToSpawn)
    {
        FVector SpawnLocation = GetRandomPointInBox();
        FRotator SpawnRotation = FRotator::ZeroRotator;

        GetWorld()->SpawnActor<AActor>(BlueprintToSpawn, SpawnLocation, SpawnRotation);
    }
}
