// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "FindPointAroundPlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GLADIATORS_API UFindPointAroundPlayer : public UBTService
{
	GENERATED_BODY()
	
protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, Category = "Search", meta = (AllowProtectedAccess = "true"))
		float SearchRadius = 1500.0f;


	UPROPERTY(EditAnywhere, Category = "Search", meta = (AllowProtectedAccess = "true"))
		float MaxRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Search", meta = (AllowProtectedAccess = "true"))
		float MinRadius = 450.0f;

};
