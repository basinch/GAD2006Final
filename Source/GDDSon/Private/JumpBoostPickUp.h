#pragma once

#include "CoreMinimal.h"
#include "BasePickUp.h"
#include "JumpBoostPickUp.generated.h"

UCLASS()
class AJumpBoostPickUp : public ABasePickUp
{
    GENERATED_BODY()

public:
    virtual void Apply() override;
};
