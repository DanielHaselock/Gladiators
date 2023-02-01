// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "DetourCrowdAIController.h"
#include "EnemyAiController.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORS_API AEnemyAiController : public AAIController
{
	GENERATED_BODY()
	

public:
	
	AEnemyAiController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;
	class UBlackboardComponent* get_blackboard() const;
	AActor* GetFlag();

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_treeComponent;


	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;


	class UBlackboardComponent* blackboard;



	class UAISenseConfig_Sight* sight_config;



	UFUNCTION()


	void on_target_detected(AActor* actor, FAIStimulus const stimulus);


	AActor* Flag;
};
