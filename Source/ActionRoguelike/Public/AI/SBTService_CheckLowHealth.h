#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckLowHealth.generated.h"

UCLASS()
class ACTIONROGUELIKE_API USBTService_CheckLowHealth : public UBTService
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector IsLowHealthKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float LowHealthThreshold = 0.9f;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
