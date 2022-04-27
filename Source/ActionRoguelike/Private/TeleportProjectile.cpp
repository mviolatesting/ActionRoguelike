#include "TeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ATeleportProjectile::ATeleportProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATeleportProjectile::OnActorOverlap);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void ATeleportProjectile::ShowExplosion()
{
	
}

void ATeleportProjectile::TeleportInstigator()
{
	GetInstigator()->SetActorLocation(GetActorLocation());
	Destroy();
}

void ATeleportProjectile::ShowExplosion_TimeElapsed()
{
	ShowExplosion();
}

void ATeleportProjectile::TeleportInstigator_TimeElapsed()
{
	TeleportInstigator();
}

void ATeleportProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		ShowExplosion();
		GetWorldTimerManager().ClearTimer(TimerHandle_Explode);
		GetWorldTimerManager().ClearTimer(TimerHandle_Teleport);

		GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this,
			&ATeleportProjectile::TeleportInstigator_TimeElapsed, 0.2f);
	}
}

void ATeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Explode, this,
		&ATeleportProjectile::ShowExplosion_TimeElapsed, 0.2f);

	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this,
		&ATeleportProjectile::TeleportInstigator_TimeElapsed, 0.4f);
}

void ATeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

