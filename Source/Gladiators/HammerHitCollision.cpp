// Fill out your copyright notice in the Description page of Project Settings.


#include "HammerHitCollision.h"
#include "Components/CapsuleComponent.h"
#include <Gladiators/GladiatorsCharacter.h>
#include <Gladiators/Enemy.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
AHammerHitCollision::AHammerHitCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HammerCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	HammerCollision->SetCollisionProfileName("Trigger");
	RootComponent = HammerCollision;
	HammerCollision->OnComponentBeginOverlap.AddDynamic(this, &AHammerHitCollision::OnOverLapBegin);
	HammerCollision->OnComponentEndOverlap.AddDynamic(this, &AHammerHitCollision::OnOverLapEnd);
}

// Called when the game starts or when spawned
void AHammerHitCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHammerHitCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsAttacking)
		ActorDamaged = nullptr;
}

void AHammerHitCollision::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsAttacking)
	{
		AGladiatorsCharacter* PlayerCast = Cast<AGladiatorsCharacter>(OtherActor);
		AEnemy* EnemyCast = Cast<AEnemy>(OtherActor);

		if (PlayerCast != nullptr && ActorDamaged == nullptr)
		{
			auto a = this->GetParentActor();
			UGameplayStatics::ApplyDamage(OtherActor, Cast<AEnemy>(a)->EnemyDamage, this->GetInstigatorController(), this, UDamageType::StaticClass());
			ActorDamaged = OtherActor;
			
		}

		if (EnemyCast != nullptr && ActorDamaged == nullptr)
		{
			if (!IsEnemy)
			{
				UGameplayStatics::ApplyDamage(OtherActor, 1, this->GetInstigatorController(), this, UDamageType::StaticClass());
				ActorDamaged = OtherActor;
			}
		}
		
	}

}

void AHammerHitCollision::OnOverLapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsAttacking)
	{
		AGladiatorsCharacter* PlayerCast = Cast<AGladiatorsCharacter>(OtherActor);
		AEnemy* EnemyCast = Cast<AEnemy>(OtherActor);

	}
}