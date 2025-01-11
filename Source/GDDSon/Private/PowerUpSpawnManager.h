#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawnManager.generated.h"

UCLASS()
class APowerUpSpawnManager : public AActor
{
    GENERATED_BODY()

public:
    APowerUpSpawnManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent* SpawnArea;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnInterval;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<AActor>> PowerUpBlueprints;

    UFUNCTION()
    void SpawnPowerUp();

    UFUNCTION(BlueprintPure)
    FVector GetRandomPointInSpawnArea() const;

private:
    FTimerHandle SpawnTimerHandle;
};
