#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

UCLASS()
class ABasePickUp : public AActor
{
    GENERATED_BODY()

public:
    ABasePickUp();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* PickUpMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent* CollisionSphere;

    UFUNCTION(BlueprintCallable)
    virtual void Apply();

    UFUNCTION()
    void OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);
};
