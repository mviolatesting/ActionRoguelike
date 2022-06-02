#include "AI/SBTService_CheckLowHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("SelfActor"));
		if (TargetActor)
		{
			if (const USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(
				TargetActor->GetComponentByClass(USAttributeComponent::StaticClass())))
			{
				const bool IsAtLowHealth = AttributeComponent->GetHealthPercentage() <= LowHealthThreshold;
				BlackBoardComp->SetValueAsBool(IsLowHealthKey.SelectedKeyName, IsAtLowHealth);
			}
		}
	}
}
