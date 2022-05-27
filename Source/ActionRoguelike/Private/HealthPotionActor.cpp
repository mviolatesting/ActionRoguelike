// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotionActor.h"

#include "SAttributeComponent.h"
#include "SCharacter.h"

AHealthPotionActor::AHealthPotionActor()
{
	HealthPotionMesh = CreateDefaultSubobject<UStaticMeshComponent>("HealthPotionMesh");
	RootComponent = HealthPotionMesh;
}

void AHealthPotionActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if (_isHidden) return;
	
	if (const ASCharacter* Character = Cast<ASCharacter>(InstigatorPawn))
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(
			Character->GetComponentByClass(USAttributeComponent::StaticClass()));
		
		if (AttributeComp)
		{			
			if (AttributeComp->ApplyHealthChange(HealAmount))
			{
				Hide();
			}
		}
	}
}


void AHealthPotionActor::Hide()
{
	FTimerDelegate InvisibleTimerDelegate = FTimerDelegate::CreateUObject(this, &AHealthPotionActor::Show);
	GetWorld()->GetTimerManager().SetTimer(_invisibleTimerHandler, InvisibleTimerDelegate,
		InvisibilityTime, false);
	
	HealthPotionMesh->SetVisibility(false);
	_isHidden = true;
}

void AHealthPotionActor::Show()
{
	HealthPotionMesh->SetVisibility(true);
	_isHidden = false;
}