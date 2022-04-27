#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ATeleportProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ATeleportProjectile();

protected:

	void ShowExplosion();
	void TeleportInstigator();

	void ShowExplosion_TimeElapsed();
	void TeleportInstigator_TimeElapsed();
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* EffectComp;
	
	virtual void BeginPlay() override;
	
	FTimerHandle TimerHandle_Explode;	
	FTimerHandle TimerHandle_Teleport;

public:	

	virtual void Tick(float DeltaTime) override;

};
