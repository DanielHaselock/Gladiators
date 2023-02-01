// Fill out your copyright notice in the Description page of Project Settings.


#include "AIManager.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Navigation/CrowdFollowingComponent.h"

AAIManager::AAIManager(FObjectInitializer const& object_initializer) : Super(object_initializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj2(TEXT("BehaviorTree'/Game/SuperAi/BT_SuperAi.BT_SuperAi'"));
	if (obj2.Succeeded())
	{
		AIbtree = obj2.Object;
	}
	AIbehavior_treeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("SuperBehaviorComp"));
	AIblackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("SuperBlackboardComp"));

	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), enemies);
	}

	
}

void AAIManager::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(AIbtree);
	AIbehavior_treeComponent->StartTree(*AIbtree);
}

UBlackboardComponent* AAIManager::get_blackboard()
{
	return AIblackboard;
}

TArray<AActor*> AAIManager::GetEnemies()
{
	return enemies;
}


void AAIManager::RemoveEnemy(AActor* enemy)
{
	TArray<AActor*> tmp;
	for (int i = 0; i < enemies.Num(); ++i)
	{
		if (enemies[i] != enemy)
		{
			 tmp.Add(enemies[i]);
		}
	}

	enemies = tmp;


	if (enemies.Num() == 0)
	{
		CharacterIsWin.Broadcast();
	}
}