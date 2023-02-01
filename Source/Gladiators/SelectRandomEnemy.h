// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIManager.h"
#include "SelectRandomEnemy.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GLADIATORS_API USelectRandomEnemy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	USelectRandomEnemy(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;


private:
	AActor* aicontroller;

	AAIManager* AiCast;

};
