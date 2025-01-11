#include "AICharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"

AAICharacter::AAICharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    ExplosionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionRadius"));
    ExplosionRadius->SetupAttachment(RootComponent);
    ExplosionRadius->SetSphereRadius(300.0f);
    ExplosionRadius->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ExplosionRadius->SetCollisionResponseToAllChannels(ECR_Overlap);
    ExplosionRadius->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnOverlapBegin);
    ExplosionRadius->OnComponentEndOverlap.AddDynamic(this, &AAICharacter::OnOverlapEnd);

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
    VisualMesh->SetupAttachment(RootComponent);

    Damage = 50.0f;
    ExplosionSound = nullptr;
    ExplosionEffect = nullptr;
    Health = 100.0f;
    bPlayerInRange = false;
}

void AAICharacter::BeginPlay()
{
    Super::BeginPlay();
    OnTakeAnyDamage.AddDynamic(this, &AAICharacter::OnAnyDamageTaken);
}

void AAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveTowardPlayer();
    LookAtPlayer();
}

void AAICharacter::MoveTowardPlayer()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController && PlayerController->GetPawn())
    {
        FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
        FVector Direction = (PlayerLocation - GetActorLocation()).GetSafeNormal();
        AddMovementInput(Direction, 1.0f);
    }
}

void AAICharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("OnOverlapBegin called with %s"), *OtherActor->GetName()));
    }

    if (OtherActor->IsA(ACharacter::StaticClass()))
    {
        Explode();
    }
}

void AAICharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("OnOverlapEnd called"));
    }
}

void AAICharacter::Explode()
{
    if (ExplosionEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
    }

    if (ExplosionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
    }

    TArray<AActor*> OverlappingActors;
    ExplosionRadius->GetOverlappingActors(OverlappingActors);

    for (AActor* Actor : OverlappingActors)
    {
        if (Actor->IsA(ACharacter::StaticClass()))
        {
            UGameplayStatics::ApplyDamage(Actor, Damage, GetController(), this, nullptr);
        }
    }

    Destroy();
}

void AAICharacter::OnAnyDamageTaken(AActor* DamagedActor, float ReceivedDamage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= ReceivedDamage;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health: %f"), Health));
    }

    if (Health <= 0)
    {
        Destroy();
        if (DeathSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
        }
    }
}

void AAICharacter::LookAtPlayer()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController && PlayerController->GetPawn())
    {
        FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
        FVector Direction = PlayerLocation - GetActorLocation();
        FRotator NewRotation = Direction.Rotation();
        NewRotation.Pitch = 0.0f;
        SetActorRotation(NewRotation);
    }
}
