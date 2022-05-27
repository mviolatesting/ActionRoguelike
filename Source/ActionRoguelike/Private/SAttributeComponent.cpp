// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
	HealthMax = 100;
}


bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	float PrevHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	if (PrevHealth == Health)
	{
		return false;
	}

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}
