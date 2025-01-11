#include "AttackBoostPickUp.h"
#include "NetAvatar.h"
#include "Kismet/GameplayStatics.h"

void AAttackBoostPickUp::Apply()
{
    ANetAvatar* Player = Cast<ANetAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Player)
    {
        Player->AttackBoostPicked();
    }

    Destroy();
}
