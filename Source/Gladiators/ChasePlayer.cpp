// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayer.h"
#include "EnemyAiController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AIManager.h"

UChasePlayer::UChasePlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("chase player");

}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	
	auto MainAi = UGameplayStatics::GetActorOfClass(GetWorld(), AAIManager::StaticClass());
	auto PlayerAi = owner_comp.GetAIOwner();

	UBlackboardComponent* MainAiBlack = UAIBlueprintHelperLibrary::GetBlackboard(MainAi);
	UBlackboardComponent* PlayerAiBlack = UAIBlueprintHelperLibrary::GetBlackboard(PlayerAi);
	MainAiBlack->SetValueAsBool(bb_keys::enemy_attack, false);
	PlayerAiBlack->SetValueAsBool(bb_keys::Can_See_Player, false);
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}