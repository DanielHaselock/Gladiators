// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAiController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Enemy.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include <Gladiators/GladiatorsCharacter.h>
#include <Tasks/GameplayTask_SpawnActor.h>
#include "Navigation/CrowdFollowingComponent.h"
#include "Navigation/CrowdManager.h"
AEnemyAiController::AEnemyAiController(FObjectInitializer const& object_initializer) : Super(object_initializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/Characters/Enemy/Ai/BT_EnemyAi.BT_EnemyAi'"));
	if (obj.Succeeded())
	{
		btree = obj.Object;
	}
	behavior_treeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AEnemyAiController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	behavior_treeComponent->StartTree(*btree);


	FTransform SpawnLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorTransform();


	UCrowdManager* CrowdManager = UCrowdManager::GetCurrent(GetWorld());
	if (CrowdManager)
	{
		const ICrowdAgentInterface* IAgent = Cast<ICrowdAgentInterface>(this);
		CrowdManager->UpdateAgentParams(IAgent);
	}

	UCrowdFollowingComponent* pathfol = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	if (pathfol)
	{
		pathfol->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);

		pathfol->SetCrowdSeparationWeight(2500, true);
		pathfol->SetCrowdSeparation(true, true);
	}

}
void AEnemyAiController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);

	}

}

UBlackboardComponent* AEnemyAiController::get_blackboard() const
{
	return blackboard;

}


void AEnemyAiController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString("FOUND PLAYER"));
	if (auto const ch = Cast<AGladiatorsCharacter>(actor))
	{
		get_blackboard()->SetValueAsBool(bb_keys::Can_See_Player, stimulus.WasSuccessfullySensed());
	}


}

AActor* AEnemyAiController::GetFlag()
{
	return Flag;
}