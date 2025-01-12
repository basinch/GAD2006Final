#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trickster.generated.h"

UCLASS()
class ATrickster : public AActor
{
    GENERATED_BODY()

public:
    ATrickster();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* StaticMeshStationary;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* StaticMeshFlying;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FlyingMeshSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation;

    UFUNCTION()
    void FlyTowardTarget(float DeltaTime);

    UFUNCTION()
    void OnFlyingMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    FVector StartLocation;
};
