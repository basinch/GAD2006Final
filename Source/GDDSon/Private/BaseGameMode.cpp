#include "BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void ABaseGameMode::OnPlayerDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Player ded"));

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        PlayerController->SetCinematicMode(true, false, false, true, true);
        PlayerController->GameHasEnded(nullptr, false);
    }

}
