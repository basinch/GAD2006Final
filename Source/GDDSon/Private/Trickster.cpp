#include "Trickster.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NetAvatar.h"
#include "GameFramework/DamageType.h"

ATrickster::ATrickster()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMeshStationary = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StationaryMesh"));
    RootComponent = StaticMeshStationary;
    StaticMeshStationary->SetStaticMesh(LoadObject<UStaticMesh>(
        nullptr, TEXT("/Game/trap_T-Pose.trap_T-Pose")));

    StaticMeshFlying = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlyingMesh"));
    StaticMeshFlying->SetupAttachment(RootComponent);
    StaticMeshFlying->SetStaticMesh(LoadObject<UStaticMesh>(
        nullptr, TEXT("/Game/asdasd/trap_T-Pose_kulak.trap_T-Pose_kulak")));
    StaticMeshFlying->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    StaticMeshFlying->SetGenerateOverlapEvents(true);

    FlyingMeshSpeed = 1200.0f;
    TargetLocation = FVector::ZeroVector;
}

void ATrickster::BeginPlay()
{
    Super::BeginPlay();

    StaticMeshFlying->OnComponentBeginOverlap.AddDynamic(this, &ATrickster::OnFlyingMeshOverlap);

    ANetAvatar* Player = Cast<ANetAvatar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (Player)
    {
        TargetLocation = Player->GetActorLocation();
    }

    StartLocation = StaticMeshFlying->GetComponentLocation();
}

void ATrickster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FlyTowardTarget(DeltaTime);
}

void ATrickster::FlyTowardTarget(float DeltaTime)
{
    if (TargetLocation != FVector::ZeroVector)
    {
        FVector CurrentLocation = StaticMeshFlying->GetComponentLocation();
        FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
        FVector NewLocation = CurrentLocation + (Direction * FlyingMeshSpeed * DeltaTime);

        StaticMeshFlying->SetWorldLocation(NewLocation);

        if (FVector::Dist(CurrentLocation, TargetLocation) < 10.0f)
        {
            Destroy();
        }
    }
}

void ATrickster::OnFlyingMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ANetAvatar::StaticClass()))
    {
        UGameplayStatics::ApplyDamage(OtherActor, 25.0f, nullptr, this, UDamageType::StaticClass());
    }
}
