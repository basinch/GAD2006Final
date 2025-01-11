#include "StaminaPickUp.h"
#include "NetAvatar.h"
#include "Kismet/GameplayStatics.h"

void AStaminaPickUp::Apply()
{
    ANetAvatar* Player = Cast<ANetAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Player)
    {
        Player->StaminaPicked();
    }

    Destroy();
}
