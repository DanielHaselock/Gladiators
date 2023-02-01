// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectRandomEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"

USelectRandomEnemy::USelectRandomEnemy(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("select enemy");
	if (UWorld* World = GetWorld())
	{
		aicontroller = UGameplayStatics::GetActorOfClass(GetWorld(), AAIManager::StaticClass());
	}
	AiCast = Cast<AAIManager>(aicontroller);
}

EBTNodeResult::Type USelectRandomEnemy::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	if (AiCast->GetEnemies().Num() > 0)
	{
		auto const cont = Cast<AAIManager>(owner_comp.GetAIOwner());

		cont->get_blackboard()->SetValueAsBool(bb_keys::enemy_attack, true);

		int random = FMath::RandRange(0, AiCast->GetEnemies().Num() - 1);
		AActor* ai = Cast<AActor>(AiCast->GetEnemies()[random]);

		if (ai)
		{
			UBlackboardComponent* comp = UAIBlueprintHelperLibrary::GetBlackboard(ai);

			comp->SetValueAsBool(bb_keys::Can_See_Player, true);


			FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
