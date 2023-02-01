// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Enemy.h"
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyAttack.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORS_API UEnemyAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

private:
	UPROPERTY(EditAnywhere, Category = Blackboard)
		FBlackboardKeySelector actor;

	AEnemy* Enemy;

};
