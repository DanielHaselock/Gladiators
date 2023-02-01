// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttack.h"

#include "EnemyAiController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "blackboard_keys.h"
#include "GameFramework/CharacterMovementComponent.h"
EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const cont = Cast<AEnemyAiController>(owner_comp.GetAIOwner());
	UBlackboardComponent* Blackboard = owner_comp.GetBlackboardComponent();
	AActor* a = cont->GetPawn();
	Enemy = Cast<AEnemy> (a);


	if ((a->GetActorLocation() - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()).Size() < 120)
	{
		Enemy->Attack();
	}
	return EBTNodeResult::Succeeded;
}
