#pragma once

#include "CoreMinimal.h"
#include "BasePickUp.h"
#include "StaminaPickUp.generated.h"

UCLASS()
class AStaminaPickUp : public ABasePickUp
{
    GENERATED_BODY()

public:
    virtual void Apply() override;
};
