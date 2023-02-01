// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateManager.h"
#include <Gladiators/GladiatorsCharacter.h>
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameOver.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void AGameStateManager::BeginPlay()
{
	Super::BeginPlay();
	AGladiatorsCharacter* GladiatorChar = (AGladiatorsCharacter*)(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UDamageComponent* DamageComp = Cast<UDamageComponent>(GladiatorChar->FindComponentByClass(UDamageComponent::StaticClass()));
	DamageComp->CharacterIsDead.AddDynamic(this, &AGameStateManager::GameOver);
	aicontroller = Cast<AAIManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AAIManager::StaticClass()));
	aicontroller->CharacterIsWin.AddDynamic(this, &AGameStateManager::YouWin);

	SetActorTickEnabled(true);
}

void AGameStateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DeathMessageOn)
	{
		OpacityLvl += DeltaTime * 0.3;
		GameOverHUD->SetOpacity(OpacityLvl);
		if (OpacityLvl >= 1)
		{
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		}
	}
}

void AGameStateManager::GameOver()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	UWidgetLayoutLibrary::RemoveAllWidgets(Player);
	if (WidgetClass != nullptr)
	{
		GameOverHUD = CreateWidget<UGameOver>(GetWorld()->GetFirstPlayerController(), WidgetClass);
		if (GameOverHUD != nullptr)
		{
			GameOverHUD->AddToViewport(9999);
			GameOverHUD->SetOpacity(0);
			DeathMessageOn = true;
		}
	}
}

void AGameStateManager::YouWin()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	UWidgetLayoutLibrary::RemoveAllWidgets(Player);
	if (WidgetClass2 != nullptr)
	{
		GameOverHUD = CreateWidget<UGameOver>(GetWorld()->GetFirstPlayerController(), WidgetClass2);
		if (GameOverHUD != nullptr)
		{
			GameOverHUD->AddToViewport(9999);
			GameOverHUD->SetOpacity(0);
			DeathMessageOn = true;
		}
	}
}

AGameStateManager::AGameStateManager()
{
	PrimaryActorTick.bCanEverTick = true;
}
