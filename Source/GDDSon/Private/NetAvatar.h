#pragma once

#include "CoreMinimal.h"
#include "NetBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "NetAvatar.generated.h"

UCLASS()
class ANetAvatar : public ANetBaseCharacter
{
    GENERATED_BODY()

public:
    ANetAvatar();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UCameraComponent* Camera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USpringArmComponent* SpringArm;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Stamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaRegenSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float JumpStaminaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackStaminaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ProjectileClass;

    UFUNCTION()
    void OnAnyDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
        AController* InstigatedBy, AActor* DamageCauser);

    void ResetDoubleJumpCount();

    void HealthPicked();
    void StaminaPicked();
    void JumpBoostPicked();
    void AttackBoostPicked();

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void Jump();
    void Attack();

    void RegenerateStamina(float DeltaTime);
    void OnPlayerDeath();

    int32 DoubleJumpCount;

    float MovementScale;
    float JumpPower;
    int32 MaxDoubleJumpCount;

    FTimerHandle StaminaBoostTimerHandle;
    FTimerHandle JumpBoostTimerHandle;
    FTimerHandle AttackBoostTimerHandle;
};
