#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class ASpawnManager : public AActor
{
    GENERATED_BODY()

public:
    ASpawnManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent* SpawnArea;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnInterval;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AAICharacter> ActorToSpawn;

    UFUNCTION()
    void SpawnActor();

    UFUNCTION(BlueprintPure)
    FVector GetRandomPointInSpawnArea() const;

private:
    FTimerHandle SpawnTimerHandle;
};
