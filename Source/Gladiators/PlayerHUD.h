// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

		UPROPERTY(meta = (BindWidget))
		class UProgressBar* LifeProgressBar;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		float LowLifeRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		float HighLifeRatio;

public:
	void SetLife(float NewLife);
	FLinearColor InterpolateColor(FLinearColor color1, FLinearColor color2, float NewLife);
};
