#include "SpawnManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "AICharacter.h"
#include "GameFramework/Controller.h"

ASpawnManager::ASpawnManager()
{
    PrimaryActorTick.bCanEverTick = true;

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    RootComponent = SpawnArea;

    SpawnInterval = 15.0f;
}

void ASpawnManager::BeginPlay()
{
    Super::BeginPlay();

    if (ActorToSpawn)
    {
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnManager::SpawnActor, SpawnInterval, true);
    }
}

void ASpawnManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASpawnManager::SpawnActor()
{
    if (!ActorToSpawn)
    {
        return;
    }

    FVector SpawnLocation = GetRandomPointInSpawnArea();
    FRotator SpawnRotation = FRotator::ZeroRotator;

    AAICharacter* SpawnedCharacter = GetWorld()->SpawnActor<AAICharacter>(ActorToSpawn, SpawnLocation, SpawnRotation);
    if (SpawnedCharacter)
    {
        if (!SpawnedCharacter->Controller)
        {
            SpawnedCharacter->SpawnDefaultController();
        }

        SpawnedCharacter->MoveTowardPlayer();
    }
}

FVector ASpawnManager::GetRandomPointInSpawnArea() const
{
    if (!SpawnArea)
    {
        return FVector::ZeroVector;
    }

    FVector Origin = SpawnArea->Bounds.Origin;
    FVector Extent = SpawnArea->GetScaledBoxExtent();

    return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}
