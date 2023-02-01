// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"
#include <Gladiators/PlayerHUD.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Enemy.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//MaxLife = 10;
	Life = MaxLife;

}

// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UDamageComponent::TakeDamage);
		if (WidgetClass != nullptr)
		{
			PlayerHUD = CreateWidget<UPlayerHUD>(Cast<APlayerController>(Owner->GetController()), WidgetClass);
			if (PlayerHUD != nullptr)
			{
				PlayerHUD->AddToViewport(9999);
				//Owner->OnTakeAnyDamage.AddDynamic(this, &AGladiatorsCharacter::TakeDamage);
				PlayerHUD->SetLife(1);
			}
		}
		Skin = Owner->GetMesh()->CreateDynamicMaterialInstance(0);
		ArmorSkin = Owner->GetMesh()->CreateDynamicMaterialInstance(1);
		Owner->GetMesh()->SetMaterial(0, Skin);
		Owner->GetMesh()->SetMaterial(1, ArmorSkin);


	}
}

void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Timer += DeltaTime;
	if (Timer >= 0.25)
	{
		Skin->SetVectorParameterValue("HitColor", FLinearColor(0, 0, 0, 1));
		ArmorSkin->SetVectorParameterValue("HitColor", FLinearColor(0, 0, 0, 1));
	}
}

void UDamageComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
		return;

	Life = FMath::Clamp(Life - Damage, 0.0f, MaxLife);

	if(PlayerHUD != nullptr)
		PlayerHUD->SetLife(Life / MaxLife);

	Skin->SetVectorParameterValue("HitColor", FLinearColor(1, 0, 0, 1));
	ArmorSkin->SetVectorParameterValue("HitColor", FLinearColor(1, 0, 0, 1));
	Timer = 0;

	if (Life <= 0)
	{
		IsDead = true;
		Owner->GetMovementComponent()->Deactivate();
		Owner->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		CharacterIsDead.Broadcast();
		this->Deactivate();
	}
}