#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

UCLASS()
class ABaseGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    void OnPlayerDeath();

};
