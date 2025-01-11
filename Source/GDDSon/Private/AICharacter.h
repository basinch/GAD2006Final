#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS()
class AAICharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AAICharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent* ExplosionRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMeshComponent* VisualMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USoundBase* ExplosionSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USoundBase* DeathSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UParticleSystem* ExplosionEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;

    UFUNCTION(BlueprintCallable)
    void Explode();
    void MoveTowardPlayer();
    void LookAtPlayer();
private:

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void OnAnyDamageTaken(AActor* DamagedActor, float ReceivedDamage, const UDamageType* DamageType,
        AController* InstigatedBy, AActor* DamageCauser);

    bool bPlayerInRange;
};
