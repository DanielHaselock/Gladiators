// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPointAroundPlayer.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "EnemyAiController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "blackboard_keys.h"

#include "GameFramework/Actor.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Gameframework/CharacterMovementComponent.h"
void UFindPointAroundPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto const cont = Cast<AEnemyAiController>(OwnerComp.GetAIOwner());
	auto const Enemy = cont->GetPawn();


	//obtain pawn location -> use as origin
	FVector const origin = Enemy->GetActorLocation();
	FNavLocation loc;
	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	float distance;
	FVector MyCharacterPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();


	cont->SetFocus(GetWorld()->GetFirstPlayerController()->GetPawn());
	while (true)
	{
		distance = (MyCharacterPosition - origin).Size();
		if (distance < MaxRadius && distance > MinRadius)
		{
			//don't move
			UPawnMovementComponent* movement = Enemy->GetMovementComponent();
			movement->StopMovementImmediately();
			cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, Enemy->GetActorLocation());
		}
		else if (distance > MaxRadius)
		{
			cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, MyCharacterPosition);
		
		} 
		break;
	}
}