// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAiController.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "AIManager.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInstigated2);
UCLASS()
class GLADIATORS_API AAIManager : public AAIController
{
	GENERATED_BODY()


public:
	AAIManager(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;

	UBlackboardComponent* get_blackboard();

	TArray<AActor*> GetEnemies();

	void RemoveEnemy(AActor* enemy);
	FInstigated2 CharacterIsWin;

private:

	//EnemyAiController[] EnemyControllers;
	TArray<AActor*> enemies;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* AIbehavior_treeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* AIbtree;


	class UBlackboardComponent* AIblackboard;

	
};
