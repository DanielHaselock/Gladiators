// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DamageComponent.h"
#include "AIManager.h"
#include "GameStateManager.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORS_API AGameStateManager : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UGameOver* GameOverHUD;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameOver> WidgetClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameOver> WidgetClass2;

	bool DeathMessageOn = false;

	float OpacityLvl = 0;
	AAIManager* aicontroller;


public:
	virtual void BeginPlay() override;
	UFUNCTION()
	void YouWin();

	void Tick(float DeltaTime) override;

	UFUNCTION()
	void GameOver();

	AGameStateManager();
};
