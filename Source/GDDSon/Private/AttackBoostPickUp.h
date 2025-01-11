#pragma once

#include "CoreMinimal.h"
#include "BasePickUp.h"
#include "AttackBoostPickUp.generated.h"

UCLASS()
class AAttackBoostPickUp : public ABasePickUp
{
    GENERATED_BODY()

public:
    virtual void Apply() override;
};
