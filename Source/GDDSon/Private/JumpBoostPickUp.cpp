#include "JumpBoostPickUp.h"
#include "NetAvatar.h"
#include "Kismet/GameplayStatics.h"

void AJumpBoostPickUp::Apply()
{
    ANetAvatar* Player = Cast<ANetAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Player)
    {
        Player->JumpBoostPicked();
    }

    Destroy();
}
