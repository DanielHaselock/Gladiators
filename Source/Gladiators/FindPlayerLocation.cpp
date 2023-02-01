// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "EnemyAiController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "blackboard_keys.h"


UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");
	
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	//get player character + enemy controller
	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const cont = Cast<AEnemyAiController>(owner_comp.GetAIOwner());

	cont->get_blackboard()->SetValueAsVector(bb_keys::Old_Point, cont->GetPawn()->GetActorLocation());
	cont->get_blackboard()->SetValueAsObject(bb_keys::target_player, Cast<UObject>(Player));
	//finish with success
	FinishLatentTask(owner_comp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}
