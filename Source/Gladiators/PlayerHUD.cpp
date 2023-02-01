// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include <Gladiators/GladiatorsCharacter.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/UMG/Public/Components/ProgressBar.h>

void UPlayerHUD::SetLife(float NewLife)
{
	FLinearColor red = FLinearColor::Red;
	FLinearColor green = FLinearColor::Green;

	LifeProgressBar->SetPercent(NewLife);
	LifeProgressBar->SetFillColorAndOpacity(InterpolateColor(red, green, NewLife));
}

FLinearColor UPlayerHUD::InterpolateColor(FLinearColor color1, FLinearColor color2, float NewLife)
{
	float fraction = FMath::Clamp((NewLife - LowLifeRatio) * (1 / (HighLifeRatio - LowLifeRatio)), 0, 1);
	FLinearColor LerpedColor;
	LerpedColor.R = (color2.R - color1.R) * fraction + color1.R;
	LerpedColor.G = (color2.G - color1.G) * fraction + color1.G;
	LerpedColor.B = (color2.B - color1.B) * fraction + color1.B;
	return LerpedColor;
}