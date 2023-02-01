// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Engine/SkeletalMesh.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "blackboard_keys.h"
#include "EnemyAiController.h"
#include <Runtime/Landscape/Classes/LandscapeProxy.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "DamageComponent.h"
#include "AIManager.h"
#include "Components/CapsuleComponent.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultLife = Life;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkinMeshAsset(TEXT("SkeletalMesh'/Game/Characters/DwarfGrunt/SkelMesh/DwarfGrunt_R_new.DwarfGrunt_R_new'"));
	
	if (SkinMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkinMeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
		GetMesh()->SetRelativeScale3D(FVector(0.9f, 0.7f, 1.5f));


		AttachHammer();
	}


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AEnemy::EnemyTakeDamage);

	UDamageComponent* DamageComp = Cast<UDamageComponent>(FindComponentByClass(UDamageComponent::StaticClass()));
	DamageComp->CharacterIsDead.AddDynamic(this, &AEnemy::Kill);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;
	if (IsAttackingEnemy)
	{
		if (Timer >= AnimationTime)
		{
			GetCharacterMovement()->Activate();
			IsAttackingEnemy = false;

		}
	}	
}


void AEnemy::AttachHammer()
{
	HammerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WarHammer"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> HammerMeshAsset(TEXT("SkeletalMesh'/Game/Characters/DwarfGrunt/SkelMesh/WarHammer.WarHammer'"));
	if (HammerMeshAsset.Succeeded())
	{
		HammerMesh->SetSkeletalMesh(HammerMeshAsset.Object);
		HammerMesh->SetupAttachment(GetMesh(), FName(TEXT("WeaponPoint")));
		//HammerMesh->SetRelativeLocation(FVector());
		
	}


}
void AEnemy::EnemyTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < 0)
		return;
	
	Life = FMath::Clamp(Life - Damage, 0.0f, DefaultLife);


}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Attack()
{
	if (!IsAttackingEnemy)
	{
		IsAttackingEnemy = true;
		
		AnimationTime = PlayAnimMontage(AttackAnimation, 1);
		GetCharacterMovement()->Deactivate();
		Timer = 0;
	}
}

void AEnemy::Kill()
{
	AAIManager* MainAi = Cast<AAIManager>(UGameplayStatics::GetActorOfClass(GetWorld(),AAIManager::StaticClass()));
	if(MainAi)
		MainAi->RemoveEnemy(this);

	GetMovementComponent()->Deactivate();
	
	AEnemyAiController* controller = Cast<AEnemyAiController>(UAIBlueprintHelperLibrary::GetAIController(this));
	if(controller)
		controller->Destroy();

	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->DestroyComponent();
}