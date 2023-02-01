// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HammerHitCollision.h"
#include "Enemy.generated.h"

UCLASS()
class GLADIATORS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	UPROPERTY(editAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* HammerMesh;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
		float Life;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
		int DefaultLife;
	UFUNCTION()
		void AttachHammer();
	UFUNCTION()
		void EnemyTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackAnimation;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void Attack();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	float AnimationTime;
	float Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
		bool IsAttackingEnemy = false;

	UFUNCTION()
		void Kill();

	UPROPERTY(EditAnywhere)
		float EnemyDamage = 1;

private:

	
};
