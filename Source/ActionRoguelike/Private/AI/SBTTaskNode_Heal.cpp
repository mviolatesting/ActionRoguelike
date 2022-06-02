#include "AI/SBTTaskNode_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTaskNode_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController && MyController->GetPawn()))
	{
		if (USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(
						MyController->GetPawn()->GetComponentByClass(USAttributeComponent::StaticClass())))
		{
			AttributeComponent->ApplyHealthChange(MyController, AttributeComponent->GetHealthMax());
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
