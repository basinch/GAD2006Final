#include "PowerUpSpawnManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

APowerUpSpawnManager::APowerUpSpawnManager()
{
    PrimaryActorTick.bCanEverTick = true;

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    RootComponent = SpawnArea;

    SpawnInterval = 10.0f;
}

void APowerUpSpawnManager::BeginPlay()
{
    Super::BeginPlay();

    if (PowerUpBlueprints.Num() > 0)
    {
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APowerUpSpawnManager::SpawnPowerUp, SpawnInterval, true);
    }
}

void APowerUpSpawnManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APowerUpSpawnManager::SpawnPowerUp()
{
    if (PowerUpBlueprints.Num() == 0)
    {
        return;
    }

    FVector SpawnLocation = GetRandomPointInSpawnArea();
    FRotator SpawnRotation = FRotator::ZeroRotator;

    int32 RandomIndex = FMath::RandRange(0, PowerUpBlueprints.Num() - 1);
    TSubclassOf<AActor> SelectedBlueprint = PowerUpBlueprints[RandomIndex];

    GetWorld()->SpawnActor<AActor>(SelectedBlueprint, SpawnLocation, SpawnRotation);
}

FVector APowerUpSpawnManager::GetRandomPointInSpawnArea() const
{
    if (!SpawnArea)
    {
        return FVector::ZeroVector;
    }

    FVector Origin = SpawnArea->Bounds.Origin;
    FVector Extent = SpawnArea->GetScaledBoxExtent();

    return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}
