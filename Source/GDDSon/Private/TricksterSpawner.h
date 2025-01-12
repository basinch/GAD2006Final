#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TricksterSpawner.generated.h"

UCLASS()
class ATricksterSpawner : public AActor
{
    GENERATED_BODY()

public:
    ATricksterSpawner();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UBoxComponent* SpawnArea;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> BlueprintToSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnInterval;

    UFUNCTION(BlueprintPure)
    FVector GetRandomPointInBox() const;

    UFUNCTION()
    void SpawnBlueprint();

private:
    FTimerHandle SpawnTimerHandle;
};
