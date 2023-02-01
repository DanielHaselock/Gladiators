// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInstigated);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GLADIATORS_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UPlayerHUD* PlayerHUD;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UPlayerHUD> WidgetClass;

	ACharacter* Owner;

	UMaterialInstanceDynamic* Skin;
	UMaterialInstanceDynamic* ArmorSkin;

	float Timer;

	bool DamageColor;

public:
	// Sets default values for this component's properties
	UDamageComponent();

	FInstigated CharacterIsDead;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool IsDead = false;

	UFUNCTION()
		void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};