// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HammerHitCollision.generated.h"

UCLASS()
class GLADIATORS_API AHammerHitCollision : public AActor
{
	GENERATED_BODY()

	AActor* ActorDamaged = nullptr;
	
public:
	// Sets default values for this actor's properties
	AHammerHitCollision();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* HammerCollision;

	UFUNCTION()
		void OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverLapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsEnemy = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};