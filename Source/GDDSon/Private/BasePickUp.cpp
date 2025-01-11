#include "BasePickUp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NetAvatar.h"

ABasePickUp::ABasePickUp()
{
    PrimaryActorTick.bCanEverTick = true;

    PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
    RootComponent = PickUpMesh;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->SetupAttachment(PickUpMesh);
    CollisionSphere->SetSphereRadius(100.0f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABasePickUp::OnCollisionEnter);
}

void ABasePickUp::BeginPlay()
{
    Super::BeginPlay();
}

void ABasePickUp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABasePickUp::Apply()
{
    UE_LOG(LogTemp, Warning, TEXT("Apply"));
}

void ABasePickUp::OnCollisionEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ANetAvatar::StaticClass()))
    {
        Apply();
        Destroy();
    }
}
