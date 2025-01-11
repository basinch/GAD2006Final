#include "HealthPickUp.h"
#include "NetAvatar.h"
#include "Kismet/GameplayStatics.h"

void AHealthPickUp::Apply()
{
    ANetAvatar* Player = Cast<ANetAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Player)
    {
        Player->HealthPicked();
    }

    Destroy();
}
