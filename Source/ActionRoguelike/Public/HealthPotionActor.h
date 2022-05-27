// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "HealthPotionActor.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AHealthPotionActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	

	AHealthPotionActor();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:

	void Hide();
	void Show();

	UPROPERTY(EditDefaultsOnly, Category="Variables")
	float HealAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category="Variables")
	float InvisibilityTime = 10.0f;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* HealthPotionMesh;

	FTimerHandle _invisibleTimerHandler;
	bool _isHidden = false;
	
};

