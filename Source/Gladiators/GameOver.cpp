// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Components/Image.h"

void UGameOver::SetOpacity(float Opacity)
{
	FLinearColor Color = YouDied->ColorAndOpacity;
	Color.A = Opacity;
	YouDied->SetColorAndOpacity(Color);
}
