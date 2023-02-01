#pragma once
#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
namespace bb_keys
{
	TCHAR const* const target_location = TEXT("TargetLocation");
	TCHAR const* const Can_See_Player = TEXT("CanSeePlayer");
	TCHAR const* const target_player = TEXT("Target");

	TCHAR const* const Is_Close = TEXT("IsCloseToTarget");
	TCHAR const* const Old_Point = TEXT("OldLocation");
	//SUPER AI KEYS

	TCHAR const* const ai_manager_chosen_enemy = TEXT("ChosenEnemy");
	TCHAR const* const enemy_attack = TEXT("EnemyAttacking");
}
