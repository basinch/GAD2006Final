#pragma once

#include "CoreMinimal.h"
#include "BasePickUp.h"
#include "HealthPickUp.generated.h"

UCLASS()
class AHealthPickUp : public ABasePickUp
{
    GENERATED_BODY()

public:
    virtual void Apply() override;
};
