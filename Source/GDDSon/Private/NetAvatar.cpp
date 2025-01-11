#include "NetAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseGameMode.h"
#include "TimerManager.h"

ANetAvatar::ANetAvatar() :
    MovementScale(1.0f),
    JumpPower(600.0f),
    MaxDoubleJumpCount(2),
    DoubleJumpCount(0),
    Health(100.0f),
    Stamina(100.0f),
    MaxStamina(100.0f),
    StaminaRegenSpeed(5.0f),
    JumpStaminaCost(15.0f),
    AttackStaminaCost(20.0f)
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

    static ConstructorHelpers::FClassFinder<AActor> ProjectileBP(TEXT("/Game/Blueprints/BP_Projectile.BP_Projectile_C"));
    if (ProjectileBP.Succeeded())
    {
        ProjectileClass = ProjectileBP.Class;
    }
}

void ANetAvatar::BeginPlay()
{
    Super::BeginPlay();

    Camera->bUsePawnControlRotation = false;
    SpringArm->bUsePawnControlRotation = true;
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;

    OnTakeAnyDamage.AddDynamic(this, &ANetAvatar::OnAnyDamageTaken);
}

void ANetAvatar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Health <= 0.0f)
    {
        OnPlayerDeath();
    }

    RegenerateStamina(DeltaTime);
}

void ANetAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("MoveForward", this, &ANetAvatar::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ANetAvatar::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ANetAvatar::Jump);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ANetAvatar::Attack);
}

void ANetAvatar::MoveForward(float Amount)
{
    FRotator Rotation = GetController()->GetControlRotation();
    FRotator YawRotation(0, Rotation.Yaw, 0);
    FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardDirection, MovementScale * Amount);
}

void ANetAvatar::MoveRight(float Amount)
{
    FRotator Rotation = GetController()->GetControlRotation();
    FRotator YawRotation(0, Rotation.Yaw, 0);
    FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(RightDirection, MovementScale * Amount);
}

void ANetAvatar::Jump()
{
    if (Stamina >= JumpStaminaCost)
    {
        if (GetCharacterMovement()->IsFalling())
        {
            if (DoubleJumpCount < MaxDoubleJumpCount)
            {
                LaunchCharacter(FVector(0, 0, JumpPower), false, true);
                DoubleJumpCount++;
            }
        }
        else
        {
            ACharacter::Jump();
            GetCharacterMovement()->Velocity.Z = JumpPower;
            DoubleJumpCount = 0;
        }
        Stamina -= JumpStaminaCost;
    }
}

void ANetAvatar::Attack()
{
    if (Stamina >= AttackStaminaCost)
    {
        if (ProjectileClass)
        {
            FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 10.0f);
            FRotator SpawnRotation = GetActorRotation();

            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
        }
        Stamina -= AttackStaminaCost;
    }
}

void ANetAvatar::RegenerateStamina(float DeltaTime)
{
    if (Stamina < MaxStamina)
    {
        Stamina += StaminaRegenSpeed * DeltaTime;
        if (Stamina > MaxStamina)
        {
            Stamina = MaxStamina;
        }
    }
}

void ANetAvatar::OnAnyDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;

    if (Health <= 0.0f)
    {
        OnPlayerDeath();
    }
}

void ANetAvatar::OnPlayerDeath()
{
    Health = Health;
}

void ANetAvatar::ResetDoubleJumpCount()
{
    DoubleJumpCount = 0;
}

void ANetAvatar::HealthPicked()
{
    float HealthIncrease = FMath::RandRange(20.0f, 30.0f);
    Health = FMath::Clamp(Health + HealthIncrease, 0.0f, 100.0f);
}

void ANetAvatar::StaminaPicked()
{
    StaminaRegenSpeed *= 2;
    GetWorldTimerManager().SetTimer(StaminaBoostTimerHandle, [this]()
        {
            StaminaRegenSpeed /= 2;
        }, 5.0f, false);
}

void ANetAvatar::JumpBoostPicked()
{
    JumpStaminaCost = 0.0f;
    GetWorldTimerManager().SetTimer(JumpBoostTimerHandle, [this]()
        {
            JumpStaminaCost = 15.0f;
        }, 5.0f, false);
}

void ANetAvatar::AttackBoostPicked()
{
    AttackStaminaCost = 0.0f;
    GetWorldTimerManager().SetTimer(AttackBoostTimerHandle, [this]()
        {
            AttackStaminaCost = 20.0f;
        }, 5.0f, false);
}
