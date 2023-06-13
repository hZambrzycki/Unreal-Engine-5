// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/SlashHUD.h"
#include "Widget/SlashOverlay.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();


}

void ASlashHUD::PreInitializeComponents()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && SlashOverlayClass)
		{
			SlashOverlay = CreateWidget<USlashOverlay>(Controller, SlashOverlayClass);
			SlashOverlay->AddToViewport();
		}
	}
}
