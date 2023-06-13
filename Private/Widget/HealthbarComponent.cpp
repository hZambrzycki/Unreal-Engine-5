// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HealthbarComponent.h"
#include "Widget/HealthBar.h"
#include "Components/ProgressBar.h"

void UHealthbarComponent::SetHealthPercent(float Percent)
{
	if (HealthBarWidget == nullptr)
	{
		HealthBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}
	if (HealthBarWidget && HealthBarWidget->HealthBar)
	{
		HealthBarWidget->HealthBar->SetPercent(Percent);
	}
}
